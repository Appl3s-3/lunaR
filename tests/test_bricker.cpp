#include <cstdint>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <string.h>

#include "luna/miniGL.h"
#include "luna/Window.hpp"
#include "luna/BufferManager.hpp"
#include "luna/VertexArray.hpp"

#include "luna/Shader.hpp"
#include "luna/ShaderProgram.hpp"

enum class Tile {
    Empty,
    Brick,
    Cross,
    Nought
};

class Bricker {
public:
    Bricker();

    void play_move(int row, int column);
    bool fully_bricked();
    Tile active_player_tile();

    bool terminated = false;
    char active_player = 0;
    Tile board[25];
};

Bricker::Bricker() {
    for (int i = 0; i < 25; ++i) {
        board[i] = Tile::Empty;
    }
}

void Bricker::play_move(int row, int column) {
    if (board[row * 5 + column] != Tile::Empty) {
        return;
    }

    // Brick surrounding area
    int brick_row = 0;
    int brick_column = 0;

    for (int i = 0; i < 3; ++i) {

        brick_row = (row - 1) + i;

        // Check that the brick is in the vertical bounds
        if ((brick_row < 0)
        ||  (brick_row >= 5)) {
            continue;
        }

        for (int j = 0; j < 3; ++j) {
            brick_column = (column - 1) + j;
        
            // Check that the brick is in the horizontal bounds
            if ((brick_column < 0)
            ||  (brick_column >= 5)) {
                continue;
            }

            // Place a brick
            board[i * 5 + j] = Tile::Brick;
        }
    }

    // Place the player token
    board[row * 5 + column] = active_player_tile();

    // Swap the player
    active_player = !active_player;
}

bool Bricker::fully_bricked() {
    for (int i = 0; i < 25; ++i) {
        if (board[i] == Tile::Empty) {
            return false;
        }
    }

    return true;
}

Tile Bricker::active_player_tile() {
    switch (active_player) {
    case 0:
        return Tile::Cross;
    case 1:
        return Tile::Nought;
    }
}

/*
 * load_state_from_argv
 * Loads initial board data from argv
 * :: char*  board :: The board to populate
 * :: int    argc  :: The number of arguments in argv
 * :: char** argv  :: The arguments passed to the program
 * Returns BRICKER_TRUE on success and BRICKER_FALSE on failure
 */
char load_state_from_argv(char*  board,
                          int    argc,
                          char** argv);


/*
 * validate_arguments
 * Validates the arguments passed to the program
 * :: int    argc :: The number of arguments in argv
 * :: char** argv :: The arguments passed to the program
 * Returns BRICKER_TRUE if the arguments are valid and BRICKER_FALSE otherwise
 */
char validate_arguments(int    argc,
                        char** argv);


int main(int argc, char** argv) {
    Bricker game = Bricker();

    float grid_top = 0.8;
    float grid_bottom = -0.8;
    float grid_left = -0.8;
    float grid_right = 0.8;

    float grid_inner_width = 0.02;
    float grid_width = grid_right - grid_left;
    float grid_height = grid_top - grid_bottom;

    float cell_size = (1.0 / 5.0) * grid_width - (2 * grid_inner_width);

    std::vector<float> grid_vertex_positions;
    std::vector<uint8_t> grid_vertex_colours;
    std::vector<uint32_t> grid_indices;
    uint32_t indices_offset = 0;

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            // Vertex Positions
            float left = grid_left
                       + (((float)j / 5.0) * grid_width)
                       + grid_inner_width;
            float top = grid_top
                      - (((float)i / 5.0) * grid_height)
                      - grid_inner_width;
            float right = left + cell_size;
            float bottom = top - cell_size;

            // Left, top
            grid_vertex_positions.push_back(left);
            grid_vertex_positions.push_back(top);
            // Right, top
            grid_vertex_positions.push_back(right);
            grid_vertex_positions.push_back(top);

            // Left, bottom
            grid_vertex_positions.push_back(left);
            grid_vertex_positions.push_back(bottom);
            // Right, bottom
            grid_vertex_positions.push_back(right);
            grid_vertex_positions.push_back(bottom);

            // Indices
            grid_indices.push_back(indices_offset + 0);
            grid_indices.push_back(indices_offset + 1);
            grid_indices.push_back(indices_offset + 2);

            grid_indices.push_back(indices_offset + 1);
            grid_indices.push_back(indices_offset + 2);
            grid_indices.push_back(indices_offset + 3);

            indices_offset += 4;

            // Colours
            for (int k = 0; k < 4; ++k) {
                grid_vertex_colours.push_back(50);
                grid_vertex_colours.push_back(50);
                grid_vertex_colours.push_back(50);
            }
        }
    }

    // data info
    luna::VertexAttributeInfo position_info;
    position_info.index = 0;
    position_info.size = 2;
    position_info.type = luna::DataType::Float32;

    luna::VertexAttributeInfo colour_info;
    colour_info.index = 1;
    colour_info.size = 3;
    colour_info.type = luna::DataType::UChar;
    colour_info.normalized = GL_TRUE;

    luna::Initiate();
    luna::Window window = luna::Window(800, 800, "Bricker");

    // vbos
    luna::BufferManager position_buffer = luna::BufferManager(GL_ARRAY_BUFFER);
    position_buffer.reserve((25 * 4) * (2 * sizeof(float)));
    position_buffer.upload(0,
                           grid_vertex_positions.size() * sizeof(float),
                           grid_vertex_positions.data());

    luna::BufferManager colour_buffer = luna::BufferManager(GL_ARRAY_BUFFER);
    colour_buffer.reserve((25 * 4) * (3 * sizeof(uint8_t)));
    colour_buffer.upload(0,
                         grid_vertex_colours.size() * sizeof(uint8_t),
                         grid_vertex_colours.data());

    luna::BufferManager indices_buffer = luna::BufferManager(GL_ELEMENT_ARRAY_BUFFER);
    indices_buffer.reserve((25 * 2) * (3 * sizeof(uint32_t)));
    indices_buffer.upload(0,
                          grid_indices.size() * sizeof(uint32_t),
                          grid_indices.data());

    // vao
    luna::VertexArray bricker_vao = luna::VertexArray();
    bricker_vao.define_attribute(position_buffer, position_info, 0);
    bricker_vao.define_attribute(colour_buffer, colour_info, 0);

    // bind the ibo the the vao
    bricker_vao.bind();
    indices_buffer.bind();
    bricker_vao.unbind();

    // shaders
    std::ifstream vertex_shader_file_stream = std::ifstream("../shaders/tests/triangle.vs");
    std::stringstream vertex_shader_stream;
    vertex_shader_stream << vertex_shader_file_stream.rdbuf();
    std::string vertex_shader_body = vertex_shader_stream.str();

    std::ifstream fragment_shader_file_stream = std::ifstream("../shaders/tests/triangle.fs");
    std::stringstream fragment_shader_stream;
    fragment_shader_stream << fragment_shader_file_stream.rdbuf();
    std::string fragment_shader_body = fragment_shader_stream.str();

    luna::Shader bricker_vs = luna::Shader(luna::ShaderType::VERTEX);
    bricker_vs.append_source(vertex_shader_body);
    bricker_vs.compile();

    luna::Shader bricker_fs = luna::Shader(luna::ShaderType::FRAGMENT);
    bricker_fs.append_source(fragment_shader_body);
    bricker_fs.compile();

    luna::ShaderProgram bricker_program = luna::ShaderProgram();
    bricker_program.attach_shader(bricker_vs);
    bricker_program.attach_shader(bricker_fs);
    bricker_program.link();

    window.clear_colour(0.12, 0.12, 0.12);

    // draw the grid
    while (window.not_closed() == true) {
        window.poll();
        
        window.clear();

        bricker_program.bind();
        bricker_vao.bind();
        glDrawElements(GL_TRIANGLES, grid_indices.size(), GL_UNSIGNED_INT, 0);

        window.swap_buffers();
    }

    luna::Terminate();


    // // Game setup
    // struct bricker bricker_game;
    // bricker_game.terminated = BRICKER_FALSE;
    // bricker_game.active_player = 1;

    // // Clear the board
    // for (int i = 0; i < BRICKER_BOARD_SIZE; ++i) {
    //     bricker_game.board[i] = BRICKER_EMPTY;
    // }

    // // The program was ran with arguments
    // if (argc > 1) {
    //     // Load the game
    //     char load_success = load_state_from_argv(bricker_game.board,
    //                                              argc,
    //                                              argv);
        
    //     // The game failed to load successfully
    //     if (load_success == BRICKER_FALSE) {
    //         return 0;
    //     }
    // }

    // // Game start
    // printf(BRICKER_WELCOME_TEXT);
    // while (bricker_game.terminated == BRICKER_FALSE) {
    //     play_turn(&bricker_game);
    // }

    return 0;
}
/*
void play_turn(struct bricker* bricker_game) {
    // Display the board
    display_board(bricker_game->board);

    // Check if the board is full
    if (fully_bricked(bricker_game->board) == BRICKER_TRUE) {
        // The player not currently active has won the game
        // Convert [1, 2] to [2, 1]
        const int winner = get_inactive_player(bricker_game->active_player);
        printf("Player %d Wins!\n", winner);

        // End the game
        bricker_game->terminated = BRICKER_TRUE;

        return;
    }

    char play_success = BRICKER_FALSE;
    // Take input until the move is valid
    while (play_success != BRICKER_TRUE) {
        // Get the input move
        struct player_move move = {
            bricker_game->active_player,
            0,
            0
        };

        printf("Player %d turn: ", move.player);
        scanf("%d %d", &(move.row), &(move.column));

        // Play the move
        play_success = play_move(bricker_game->board, &move);
    }

    // Swap the active player
    bricker_game->active_player = get_inactive_player(bricker_game->active_player);
}

char play_move(char*               board,
               struct player_move* move) {
    // Validate the move
    char valid_move = validate_move(board, move->row, move->column);
    if (valid_move == BRICKER_FALSE) {
        printf(BRICKER_INVALID_MOVE_TEXT);
        return BRICKER_FALSE;
    }

    // Get the player token
    char player_token = BRICKER_PLAYER_1_TOKEN;
    if (move->player == 2) {
        player_token = BRICKER_PLAYER_2_TOKEN;
    }

    // Play the move
    int brick_row = move->row - 1;
    int brick_column = move->row - 1;

    // Place a 3x3 grid of bricks
    for (int i = 0; i < BRICKER_BRICK_GRID_SIZE; ++i) {
        brick_row = (move->row - 1) + i;

        // Check that the brick is in the vertical bounds
        if ((brick_row < 0)
        ||  (brick_row > (BRICKER_COLUMN_SIZE - 1))) {
            continue;
        }

        for (int j = 0; j < BRICKER_BRICK_GRID_SIZE; ++j) {
            brick_column = (move->column - 1) + j;
        
            // Check that the brick is in the horizontal bounds
            if ((brick_column < 0)
            ||  (brick_column > (BRICKER_ROW_SIZE - 1))) {
                continue;
            }

            // Place a brick
            set_board_cell(board, brick_row, brick_column, BRICKER_BRICK);
        }
    }

    // Place the player token
    set_board_cell(board, move->row, move->column, player_token);

    return BRICKER_TRUE;
}

char load_state_from_argv(char*  board,
                          int    argc,
                          char** argv) {
    // Validate arguments
    char valid_arguments = validate_arguments(argc, argv);
    if (valid_arguments == BRICKER_FALSE) {
        return BRICKER_FALSE;
    }
    
    // Populate board state
    for (int i = 0; i < BRICKER_BOARD_SIZE; ++i) {
        // Convert 'E's in the data string to ' 's
        switch (argv[1][i]) {
        case 'E':
            board[i] = BRICKER_EMPTY;
            break;

        default:
            board[i] = argv[1][i];
        }
    }

    return BRICKER_TRUE;
}

char validate_arguments(int    argc,
                        char** argv) {
    // Incorrect number of arguments
    if (argc > 2) {
        printf(BRICKER_INVALID_ARGUMENT_COUNT);
        return BRICKER_FALSE;
    }

    // Initial board data is of incorrect length
    // or initial board data contains unexpected characters
    if ((strlen(argv[1]) < BRICKER_BOARD_SIZE)
    ||  (string_only_contains(argv[1], BRICKER_DATA_TOKENS) == 0)) {
        printf(BRICKER_INVALID_INITIAL_DATA);
        return BRICKER_FALSE;
    }
}
*/