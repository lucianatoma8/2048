    - am rezolvat toate cele 5 cerinte astfel:

    1.
        -> optiunile din meniu sunt pointeri catre siruri de caractere,
    stocati intr-un vector, pt optiuni

        -> optiunile neselectate au culoarea fundalului,
    iar cele selectate, o alta culoare

        -> deplasarea prin meniu se face cu ajutorul sagetilor, iar alegerea
    unei optiuni se face cu enter
    
        -> "New Game" porneste un joc nou; pentru a reveni la meniu dupa 
    inceperea jocului, se apasa tasta Q, devenind posibila optiunea "Resume"
    
        -> "Resume" se poate folosi atunci cand, in timpul jocului, 
    se apasa tasta Q, care ne intoarce la meniu; prin aceasta optiune, se 
    revine la starea jocului dinainte de a apasa tasta Q; daca jocul a fost 
    anterior castigat sau pierdut si se revine la meniu, optiunea "Resume" nu 
    mai este valabila, pt ca jocul a fost practic incheiat
    
        -> "Quit" inchide aplicatia, toate informatiile se pierd

        2.
            -> functia "draw_board" defineste layout-ul ecranului de joc, 
            afisand tabla de joc(goala) in partea dreapta si panoul de control
            (tot gol) in partea stanga
    
            ->am ales culorile casutelor astfel incat sa se treaca de la o 
            nuanta de roz la una de mov si asa mai departe
            
            -> functia "start_new_game" porneste jocul, afisand 2 casute cu 
            valori din multimea{2, 4}, in mod aleator, pe tabla de joc; scorul 
            initial este setat la 0
            -> functia "display_control_panel" afiseaza data si ora curente, 
            punctajul acumulat si comenzile valide

            3.
                -> pentru deplasarea casutelor, avem functiile "move_boxes_up", 
                "move_boxes_down", "move_boxes_left", "move_boxes_right"
                -> pentru imbinarea casutelor identice in urma deplasarii avem 
                functiile "combine_boxes_up", "combine_boxes_down", 
                "combine_boxes_left", "combine_boxes_right"; scorul creste cu 
                fiecare imbinare realizata
                -> pentru mutarile complete ale casutelor avem functiile 
                "moveup", "movedown", "moveleft", "moveright"
                -> dupa fiecare mutare realizata, este generata aleator o noua 
                casuta cu valoarea din multimea {2, 4} si este posibila 
                optiunea de UNDO->daca miscarea introdusa este invalida, nu se 
                intampla nimic, starea jocului nu se modifica
                -> daca jocul este pierdut sau castigat, se afiseaza un mesaj 
                corespunzator si este posibila optiunea de UNDO; daca re revine 
                la meniu dupa un joc pierdut sau castigat, nu mai este posibila 
                optiunea "Resume"

                4.
                    -> functia "auto_move" se foloseste de functia 
                    "count_free_cells" pt a calcula nr de casute libere in urma 
                    fiecarei mutari posibile; daca vreuna din directii 
                    elibereaza mai multe casute, deplasarea va fi in acea 
                    directie, iar daca doate directiile elibereaza acelasi nr 
                    de casute, se alege o directie random pt deplasare

                    5.
                        -> functia "can_move" verifica daca exista mutari 
                        posibile
                        ->daca nu mai exista mutari posibile, jocul este 
                        pierdut si se afiseaza mesajul corespunzator in panoul 
                        de control
                        -> daca se ajunge la valoarea 2048 in vreo casuta, 
                        jocul e castigat si se afiseaza mesajul corespunzator 
                        in panoul de control
                        -> in urma pierderii sau castigarii jocului, jucatorul 
                        poate alege intre a incepe un joc nou, a reveni la 
                        meniu sau a iesi de tot din aplicatie; de asemenea, 
                        optiunea de UNDO este valabila si in cazul in care 
                        castigam, dar si in cazul in care pierdem jocul

                        +++++ bonusuri implementate : buton UNDO + folosirea de 
                        culori
                            -> in urma optiunii de UNDO, se realizeaza un glitch 
                            pt a fi sesizabil faptul ca s-a revenit la starea 
                            anterioara a jocului
                            -> culorile folosite au fost: 
                            init_color(1, 1000, 780, 820); // PINK fundal
                            init_color(2, 905, 625, 770);  // KOBI 2
                            init_color(3, 900, 560, 675);  // LIGHT THULIAN PINK 8
                            init_color(4, 850, 445, 630);  // PALE VIOLET RED 32
                            init_color(5, 785, 400, 510)   // MULLBERRY 128
                            init_color(6, 700, 265, 420;   // RASPBERRY ROSE 512
                            init_color(7, 625, 270, 460);  // JAZZBERRY JAM 2048
                            init_color(8, 410, 160, 375);  // PALATINATE PURPLE selectat
                            init_color(9, 830, 605, 800);  // LIGHT MEDIUM ORCHID 4
                            init_color(10, 590, 470, 715); // PURPLE MOUNTAIN MAJESTY 16
                            init_color(11, 525, 375, 555); // POMP AND POWER 64
                            init_color(12, 555, 270, 520); // PLUM 256
                            init_color(13, 345, 260, 485); // CYBER GRAPE 1024