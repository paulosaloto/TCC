const char* tabelaExpressoes[5] = {"neutro", "agressivo", "euforico", "entediado", "relaxado"};
const int       tabelaOlhos[5]  = {    4095,        3087,       4080,          15,       960 };

const byte   tabelaPosicao[][5] = {{0,  3,  7,  11,  13},
                                  {14, 15, 19, 22, 24},
                                  {26, 28, 31, 35, 37},
                                  {38, 39, 42, 45, 48},
                                  {49, 50, 54, 57, 59}};      

const int   olhos[62]           = { 4095, 0, 4095,       // 0 - Neutro-Neutro
                                    4095, 4095, 3087, 3087, // 3 - Neutro-Agressivo
                                    4095, 4095, 4080, 4080, // 7 - Neutro-Eufórico
                                    4095, 15,               // 11 - Neutro-Entediado
                                     960,                   // 13 - Neutro-Relaxado
                                    4095,                   // 14 - Agressivo-Neutro
                                    3087, 4095, 4095, 3087, // 15 - Agressivo-Agressivo
                                    3087, 4095, 4080,       // 19 - Agressivo-Eufórico
                                    3087,   15,             // 22 - Agressivo-Entediado
                                    3087,  960,             // 24 - Agressivo-Relaxado
                                    4080, 4095,             // 26 - Euforico-Neutro
                                    4080, 4095, 3087,       // 28 - Euforico-Agressivo
                                    4080, 4095, 4095, 4080, // 31 - Euforico-Eufórico
                                    4080,   15,             // 35 - Euforico-Entediado
                                     960,                   // 37 - Euforico-Relaxado
                                    4095,                   // 38 - Entediado-Neutro
                                      15, 4095, 3087,       // 39 - Entediado-Agressivo
                                      15, 4095, 4080,       // 42 - Entediado-Eufórico
                                      15,   15,   15,       // 45 - Entediado-Entediado
                                     960,                   // 48 - Entediado-Relaxado
                                    4095,                   // 49 - Relaxado-Neutro
                                     960, 4095, 3087, 3087, // 50 - Relaxado-Agressivo
                                     960, 4095, 4080,       // 54 - Relaxado-Eufórico
                                     960,   15,             // 57 - Relaxado-Entediado
                                     960,  960,  960       };// 59 - Relaxado-Relaxado

const int   numServo[6] =       {   0,    1,    2,    3,    4,    5};
const int   valorJuntaMax[6] =  {3100, 3200, 3000, 3200, 3200, 2250};//, 4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000};
const int   valorJuntaMin[6] =  {1400,  800, 1300,  800,  800, 1550};//, 1950, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
const int   expressoes[][6] =  {{1700, 3000, 1600, 3050, 2000, 2000},// 0 - Neutro-Neutro: [0] a [3]  {1700, 3000, 1600, 3050, 1800, 1900}
                                {1700, 3000, 1600, 3050, 2000, 2000},// 1 - Neutro-Neutro
                                {1700, 3000, 1600, 3050, 2000, 2000},// 2 - Neutro-Neutro
                                {2000, 1500, 2000, 1500, 2000, 2000},// 3 - Neutro-Agressivo
                                {2800, 1800, 2700, 1800, 2000, 2050},// 4 - Neutro-Agressivo
                                {2400, 1600, 2300, 1600, 2000, 2050},// 5 - Neutro-Agressivo
                                {2800, 1800, 2700, 1800, 2000, 2050},// 6 - Neutro-Agressivo
                                {1400, 1200, 1400, 1400, 2000, 2000},// 7 - Neutro-Eufórico
                                {1500, 1000, 1500, 1200, 2000, 2000},// 8 - Neutro-Eufórico
                                {1400, 1200, 1400, 1400, 2000, 2000},// 9 - Neutro-Eufórico
                                {1500, 1000, 1500, 1200, 2000, 2000},// 10 - Neutro-Eufórico
                                {2000, 2800, 1800, 3000, 1800, 2200},// 11 - Neutro-Entediado
                                {2000, 3000, 1800, 3000, 2000, 2100},// 12 - Neutro-Entediado
                                {1900, 3000, 2000, 2900, 2000, 1900},// 13 - Neutro-Relaxado
                                {1900, 3000, 2000, 2900, 2000, 2000},// 14 - Agressivo-Neutro
                                {1500, 1300, 1500, 1300, 2000, 2000},// 15 - Agressivo-Agressivo
                                {2800, 1800, 2700, 1800, 2000, 1950},// 16 - Agressivo-Agressivo
                                {2400, 1600, 2300, 1600, 2000, 2000},// 17 - Agressivo-Agressivo
                                {2800, 1800, 2700, 1800, 2000, 2050},// 18 - Agressivo-Agressivo
                                {1500, 2000, 1500, 2000, 2000, 2050},// 19 - Agressivo-Eufórico
                                {1400,  900, 1400, 1000, 2000, 1950},// 20 - Agressivo-Eufórico
                                {1500, 1000, 1500, 1200, 2000, 2000},// 21 - Agressivo-Eufórico
                                {2600, 2800, 2200, 2500, 2000, 2100},// 22 - Agressivo-Entediado
                                {2000, 3000, 1800, 3000, 2000, 2100},// 23 - Agressivo-Entediado
                                {1900, 3000, 2000, 2900, 1900, 2000},// 24 - Agressivo-Relaxado
                                {1900, 3000, 2000, 2900, 2000, 1900},// 25 - Agressivo-Relaxado
                                {1700, 1200, 1600, 2900, 2000, 2000},// 26 - Euforico-Neutro
                                {1700, 3000, 1600, 3050, 2000, 2000},// 27 - Euforico-Neutro
                                {3000, 1600, 3000, 1600, 2000, 2050},// 28 - Euforico-Agressivo
                                {2500, 1800, 2400, 1800, 2000, 2050},// 29 - Euforico-Agressivo
                                {2800, 1800, 2700, 1800, 2000, 2050},// 30 - Euforico-Agressivo
                                {1500,  800, 1500,  900, 2000, 2000},// 31 - Euforico-Eufórico
                                {1500, 1200, 1500, 1400, 2000, 2000},// 32 - Euforico-Eufórico
                                {1500,  800, 1500,  900, 2000, 2000},// 33 - Euforico-Eufórico
                                {1500, 1000, 1500, 1200, 2000, 2000},// 34 - Euforico-Eufórico
                                {1700, 2500, 1500, 1800, 2200, 2200},// 35 - Euforico-Entediado
                                {2000, 2800, 1800, 3000, 2000, 2100},// 36 - Euforico-Entediado
                                {1900, 3000, 2000, 2900, 2000, 1900},// 37 - Euforico-Relaxado
                                {1700, 3000, 1600, 3050, 2000, 2000},// 38 - Entediado-Neutro
                                {2700, 2800, 2500, 3000, 2000, 2050},// 39 - Entediado-Agressivo
                                {2000, 1800, 1800, 1800, 2000, 2050},// 40 - Entediado-Agressivo
                                {2800, 1800, 2700, 1800, 2000, 2050},// 41 - Entediado-Agressivo
                                {1800, 2800, 1700, 3000, 2000, 2000},// 42 - Entediado-Eufórico
                                {1500,  800, 1500,  900, 2000, 2000},// 43 - Entediado-Eufórico
                                {1500, 1000, 1500, 1200, 2000, 2000},// 44 - Entediado-Eufórico
                                {2000, 3000, 1800, 3000, 2200, 2000},// 45 - Entediado-Entediado
                                {2000, 3000, 1600, 3000, 2200, 2000},// 46 - Entediado-Entediado
                                {2000, 3000, 1800, 3000, 2000, 2100},// 47 - Entediado-Entediado
                                {1900, 3000, 2000, 2900, 2000, 1900},// 48 - Entediado-Relaxado
                                {1700, 3000, 1600, 3050, 2000, 2000},// 49 - Relaxado-Neutro
                                {1900, 3000, 2000, 2900, 2000, 2050},// 50 - Relaxado-Agressivo
                                {2800, 1800, 2700, 1800, 2000, 2050},// 51 - Relaxado-Agressivo
                                {1800, 1800, 1800, 1800, 2000, 2050},// 52 - Relaxado-Agressivo
                                {2800, 1800, 2700, 1800, 2000, 2050},// 53 - Relaxado-Agressivo
                                {1900,  800, 2000,  900, 1900, 2050},// 54 - Relaxado-Eufórico
                                {1500, 1200, 1500, 1400, 2000, 2000},// 55 - Relaxado-Eufórico
                                {1500, 1000, 1500, 1200, 2000, 2000},// 56 - Relaxado-Eufórico
                                {1900, 3000, 1800, 3000, 1900, 2050},// 57 - Relaxado-Entediado
                                {2000, 2800, 1800, 3000, 2000, 2100},// 58 - Relaxado-Entediado
                                {1900, 3000, 2000, 2900, 2100, 1850},// 59 - Relaxado-Relaxado
                                {1900, 3000, 2000, 3100, 2200, 1850},// 60 - Relaxado-Relaxado
                                {1900, 3000, 2000, 2900, 2000, 1900}};// 61 - Relaxado-Relaxado
/*const int   neutroAceno1[6] = {1700, 3000, 2000, 1000, 2000, 2700, 2000, 3000, 3000, 3000, 3000, 0, 0, 0, 0, 0, 0, 0, 3000};
const int   neutroAceno2[6] = {1700, 3000, 1500, 1300, 2000, 1700, 1900, 3000, 3000, 3000, 3000, 0, 0, 0, 0, 0, 0, 0, 3000};
const int   neutroAceno3[6] = {1700, 3000, 1500, 1000, 2000, 2700, 2000, 3000, 3000, 3000, 3000, 0, 0, 0, 0, 0, 0, 0, 3000};
const int   neutroAceno4[6] = {1700, 3000, 1600, 3050, 2000, 2700, 2000, 3000, 3000, 3000, 3000, 0, 0, 0, 0, 0, 0, 0, 3000};
*/



