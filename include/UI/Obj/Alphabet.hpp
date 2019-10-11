/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** include/Alphabet.hpp
*/

#ifndef ALPHABET
#define ALPHABET

    typedef struct alphabet_s {
        const char idle[256];
        const char hover[256];
        const char clicked[256];
        char c;
    } alphabet_t;

    static alphabet_t alphabet_path[41] =
    {
        {"./ressources/UI/alphabet/space.png", "./ressources/UI/alphabet/space_hover.png", "./ressources/UI/alphabet/space_clicked.png", ' '},
        {"./ressources/UI/alphabet/A.png", "./ressources/UI/alphabet/A_hover.png", "./ressources/UI/alphabet/A_clicked.png", 'A'},
        {"./ressources/UI/alphabet/B.png", "./ressources/UI/alphabet/B_hover.png", "./ressources/UI/alphabet/B_clicked.png", 'B'},
        {"./ressources/UI/alphabet/C.png", "./ressources/UI/alphabet/C_hover.png", "./ressources/UI/alphabet/C_clicked.png", 'C'},
        {"./ressources/UI/alphabet/D.png", "./ressources/UI/alphabet/D_hover.png", "./ressources/UI/alphabet/D_clicked.png", 'D'},
        {"./ressources/UI/alphabet/E.png", "./ressources/UI/alphabet/E_hover.png", "./ressources/UI/alphabet/E_clicked.png", 'E'},
        {"./ressources/UI/alphabet/F.png", "./ressources/UI/alphabet/F_hover.png", "./ressources/UI/alphabet/F_clicked.png", 'F'},
        {"./ressources/UI/alphabet/G.png", "./ressources/UI/alphabet/G_hover.png", "./ressources/UI/alphabet/G_clicked.png", 'G'},
        {"./ressources/UI/alphabet/H.png", "./ressources/UI/alphabet/H_hover.png", "./ressources/UI/alphabet/H_clicked.png", 'H'},
        {"./ressources/UI/alphabet/I.png", "./ressources/UI/alphabet/I_hover.png", "./ressources/UI/alphabet/I_clicked.png", 'I'},
        {"./ressources/UI/alphabet/J.png", "./ressources/UI/alphabet/J_hover.png", "./ressources/UI/alphabet/J_clicked.png", 'J'},
        {"./ressources/UI/alphabet/K.png", "./ressources/UI/alphabet/K_hover.png", "./ressources/UI/alphabet/K_clicked.png", 'K'},
        {"./ressources/UI/alphabet/L.png", "./ressources/UI/alphabet/L_hover.png", "./ressources/UI/alphabet/L_clicked.png", 'L'},
        {"./ressources/UI/alphabet/M.png", "./ressources/UI/alphabet/M_hover.png", "./ressources/UI/alphabet/M_clicked.png", 'M'},
        {"./ressources/UI/alphabet/N.png", "./ressources/UI/alphabet/N_hover.png", "./ressources/UI/alphabet/N_clicked.png", 'N'},
        {"./ressources/UI/alphabet/O.png", "./ressources/UI/alphabet/O_hover.png", "./ressources/UI/alphabet/O_clicked.png", 'O'},
        {"./ressources/UI/alphabet/P.png", "./ressources/UI/alphabet/P_hover.png", "./ressources/UI/alphabet/P_clicked.png", 'P'},
        {"./ressources/UI/alphabet/Q.png", "./ressources/UI/alphabet/Q_hover.png", "./ressources/UI/alphabet/Q_clicked.png", 'Q'},
        {"./ressources/UI/alphabet/R.png", "./ressources/UI/alphabet/R_hover.png", "./ressources/UI/alphabet/R_clicked.png", 'R'},
        {"./ressources/UI/alphabet/S.png", "./ressources/UI/alphabet/S_hover.png", "./ressources/UI/alphabet/S_clicked.png", 'S'},
        {"./ressources/UI/alphabet/T.png", "./ressources/UI/alphabet/T_hover.png", "./ressources/UI/alphabet/T_clicked.png", 'T'},
        {"./ressources/UI/alphabet/U.png", "./ressources/UI/alphabet/U_hover.png", "./ressources/UI/alphabet/U_clicked.png", 'U'},
        {"./ressources/UI/alphabet/V.png", "./ressources/UI/alphabet/V_hover.png", "./ressources/UI/alphabet/V_clicked.png", 'V'},
        {"./ressources/UI/alphabet/W.png", "./ressources/UI/alphabet/W_hover.png", "./ressources/UI/alphabet/W_clicked.png", 'W'},
        {"./ressources/UI/alphabet/X.png", "./ressources/UI/alphabet/X_hover.png", "./ressources/UI/alphabet/X_clicked.png", 'X'},
        {"./ressources/UI/alphabet/Y.png", "./ressources/UI/alphabet/Y_hover.png", "./ressources/UI/alphabet/Y_clicked.png", 'Y'},
        {"./ressources/UI/alphabet/Z.png", "./ressources/UI/alphabet/Z_hover.png", "./ressources/UI/alphabet/Z_clicked.png", 'Z'},
        {"./ressources/UI/alphabet/0.png", "./ressources/UI/alphabet/0_hover.png", "./ressources/UI/alphabet/0_clicked.png", '0'},
        {"./ressources/UI/alphabet/1.png", "./ressources/UI/alphabet/1_hover.png", "./ressources/UI/alphabet/1_clicked.png", '1'},
        {"./ressources/UI/alphabet/2.png", "./ressources/UI/alphabet/2_hover.png", "./ressources/UI/alphabet/2_clicked.png", '2'},
        {"./ressources/UI/alphabet/3.png", "./ressources/UI/alphabet/3_hover.png", "./ressources/UI/alphabet/3_clicked.png", '3'},
        {"./ressources/UI/alphabet/4.png", "./ressources/UI/alphabet/4_hover.png", "./ressources/UI/alphabet/4_clicked.png", '4'},
        {"./ressources/UI/alphabet/5.png", "./ressources/UI/alphabet/5_hover.png", "./ressources/UI/alphabet/5_clicked.png", '5'},
        {"./ressources/UI/alphabet/6.png", "./ressources/UI/alphabet/6_hover.png", "./ressources/UI/alphabet/6_clicked.png", '6'},
        {"./ressources/UI/alphabet/7.png", "./ressources/UI/alphabet/7_hover.png", "./ressources/UI/alphabet/7_clicked.png", '7'},
        {"./ressources/UI/alphabet/8.png", "./ressources/UI/alphabet/8_hover.png", "./ressources/UI/alphabet/8_clicked.png", '8'},
        {"./ressources/UI/alphabet/9.png", "./ressources/UI/alphabet/9_hover.png", "./ressources/UI/alphabet/9_clicked.png", '9'},
        {"./ressources/UI/alphabet/dot.png", "./ressources/UI/alphabet/dot_hover.png", "./ressources/UI/alphabet/dot_clicked.png", '.'},
        {"./ressources/UI/alphabet/double_dot.png", "./ressources/UI/alphabet/double_dot_hover.png", "./ressources/UI/alphabet/double_dot_clicked.png", ':'},
        {"./ressources/UI/alphabet/question.png", "./ressources/UI/alphabet/question_hover.png", "./ressources/UI/alphabet/question_clicked.png", '?'},
        {"NULL","NULL", "NULL", '@'},
    };

#endif