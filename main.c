/*
Main en general de las imulaciones

compilar gcc main.c presentacionWin.c -o main.execl
Solo funciona en Windows por ahora

*/

// LIBRERÍAS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "presentacion.h"
#include <locale.h>

void dibujarLogoESCOM();
void transicion_supermercado();
void transicion_banco();
void transicion_SO();
void mostrarMenu();
void imagen_menu();

//******************************************************************************************************
//	MAIN
//******************************************************************************************************
int main() {
	setlocale(LC_ALL, "es_ES.UTF-8");
	BorrarPantalla();
	EsperarMiliSeg(2000);
	dibujarLogoESCOM();
	EsperarMiliSeg(2000);
	BorrarPantalla();
	int opcion;

    do {
        mostrarMenu();
        scanf("%d", &opcion);
		BorrarPantalla();
        switch (opcion) {
            case 1:
				EsperarMiliSeg(2000);
                transicion_supermercado();
				EsperarMiliSeg(2000);
                system("\".\\Simulacion1\\supermercado.exe\"");
                break;
            case 2:
				EsperarMiliSeg(2000);
                transicion_SO();
				EsperarMiliSeg(2000);
                system("\".\\Simulacion2\\simulacionSO.exe\"");
                printf("Ejecutando Programa 2...\n");
                break;
            case 3:
				EsperarMiliSeg(2000);
                transicion_banco();
				EsperarMiliSeg(2000);
                system("\".\\Simulacion3\\banco.exe\"");
                break;
			case 4:
                printf("Saliendo...\n");
				EsperarMiliSeg(2000);
				dibujarLogoESCOM();
            break;
            default:
                printf("Opción no válida. Por favor, intente de nuevo.\n");
        }
		BorrarPantalla();
    } while (opcion != 4);
	EsperarMiliSeg(5000);
    return 0;
}

//******************************************************************************************************
//	FUNCIONES
//******************************************************************************************************

void dibujarLogoESCOM() {
    const char *logo[] = {
		"                 .  ....i..::  .i. :. .. .i    ::.r: ::.   .i .i  :   . .:. :: .   .                ",
        "                 U..7:: :. :.  ...: : i.s. v: ...:i.:  7 r7. :. : i.i:rr. .v  si r:v.:              ",
        "                 . .                              .                 .            .  :::             ",
        "                    :ULusjsJjsLus1LsL1vJYYLYvsLjsY7LvsLJsvvLLYvYYuJJvYYLLsvYLJvjYs7                 ",
        "                    :7rrrrrrrrrrrrririiiiiiiiiriiiiiiiiiiiiiiiiiririrrrrrrrrrrrrr7r                 ",
        "                                                                                                    ",
        "                                   iuJuj1susjL7irvJsuJuj1juj1j1js:                                  ",
        "                               .sBBQusYsLL77:i2BBBuYYsYJYJYJsJYsIBBBs.                              ",
        "                            :qBBd:          iPdr                   :bBBg7                           ",
        "                         7gBBU.          vRB5.                         vgBQP:                       ",
        "                     .2BBM7           7QBX:                               .1BBBs.                   ",
        "                  :EBBP:           rMBb:           :JPQBQ5PgMBREY:            idBBZr                ",
        "               7BBBs.           rgBdi           7gBMu..UBu     :1DBQ2.            LRBBX:            ",
        "            rBBMi            :EBDi           .DBdi       SB        .JQQD:            .UBQE          ",
        "           BB:              BBr             BBv           bB           iBQ               KBr        ",
        "          BI               Br             7Bv             Bg             Bg               .B.       ",
        "          B7              .B             .B             :BQ              QP                B:       ",
        "          .Bg.             7BU           :B           iBBi             sBP               rB2        ",
        "            XBBS:            SBBPi        qB.      :PBQ:            7RBq.             rZBQ:         ",
        "              .IBBQL            rdBBPL:    :BQ::JQQM7            7gBP:            .IBBQv            ",
        "                  rEBBP:            ijZRQMgSdBQXs.            igBZi            igBBX:               ",
        "                     .JBBBJ.                               iZBDi           .uBBQ7                   ",
        "                         :dBBdr                         :PBDr           iZBBP:                      ",
        "                             LQBQI.                   sg5:          .1BBQY                          ",
        "                                :KBBMYv7777777777r75BBB7::irrr7r77EBBP:                             ",
        "                                    r25SSXSKSK5X5XISuv7uUSISIS5XSX7                                 ",
        "                                                                                                    ",
        "                                                                                                    ",
        "                    sBQMMDMgggggggMgMDgDgDMgRgRggDgDgDRgRgMggggDMgRMMgRMQRRMRgMMRQZ                 ",
        "                                                                                                    ",
        "                         :iiriri7.  :rvv7:      .rLv7.     :7vvi     :        :                     ",
        "                        BBrYLsLsJ.iBKvrrvKQB  SBgU77JDB. BBqv7vXQBr  BQ1     BBv                    ",
        "                        B7        Bd       : QB        vB:       .B2 BiPB. qB:B7                    ",
        "                        B7        .QMdXIsi  .B         Br          B B. :BBg  Qv                    ",
        "                       1BQ1IqKqqZ.    .:ivBr B:        gB         qB Qi   .   B7                    ",
        "                        Bd         qi     BE :QD:    .5iDBv.    iBB  Br       B1                    ",
        "                        :srr7r7vj  .s12jUs.    .sU2UIs:   ruI1I17    1        U                     ",
    };
    
    for (int i = 0; i < 37; i++) {
		EsperarMiliSeg(50);
		MoverCursor(75-50,i);
        printf("%s", logo[i]);
    }
}

void imagen_menu() {
	MoverCursor(75-31,0);
	const char *logo[] = {
		"       EgDQ:    ii         u2i       .5Xj      .L:       .BgdB         Y2Y",
		"     .B.   B   BLvB.      BL DD     rB7:BB... IBiBq      B.  rB      rBr.XB",
		"  :riBD:r7iBPiBB  BBir7L7SB:iUBqdMDdBPv21bqEPPBqLZBZZgbXBB:r: Bi     B:   QI....",
		" BBrrBY:777i7iBQ:77vuJjYviBs.....   B.        Bi     .. 7Q.iYsXPggRDXQB752qPKqESBr",
		" 2B  gX        B          rB        7B        .B         DM           B         dB",
		"  B   B1v      :BXE:       ZBB1      KBBU      1BQ7       KQBQv       :BBv      qQ",
		"  B.  vBBB      .BBB       7BB2       BBQ      .QB:        iQBI        BBq      SB",
		"  B:   PQ:        .                                                             PR",
		"  Br                                                                            Zg",
		"  B7                                            	  /  			    QP",
		"  B7                     |\\  /|  |¯¯¯¯¯¯  |\\    | |     |                       B5",
		"  B:                     | \\/ |  |        | \\   | |     |                       Bv",
		"  B:                     |    |  |---     |  \\  | |     |                       Bi",
		"  B                      |    |  |        |   \\ | |     |                       B",
		"  B                      |    |  |______  |    \\| |_____|                       B",
		" .B                                                                            .B",
		" rB                                                                            iQ",
		" SB                                                                            vB",
		" BX                                                                            5B",
		" Br                                                                            dR",
		" B.                                                                            Rb",
		" B                                                                             Qq",
		".B                                                                             BX",
		"vB                                                                             RP",
		"XB                                                                             DD",
		"RP                                                                             SQ",
		"BS                                                                             2B",
		"BJ                                                                             LB",
		"BJ                                                                             7B",
		"BJ                                                                             rB",
		"B2                                                                             iQ",
		"BX                                                                             iB",
		".PbdgZggRgQgRggZEK2vr::.....:i7jKbDgQMRgMgRgMgRgRgMZDbbqq5XIS5KqdEgDRgMDZbbKKKZB",
		"                                                                        .::ii:."};
    
    for (int i = 0; i < 33; i++) {
		EsperarMiliSeg(50);
		MoverCursor(75-31,i);
        printf("%s\n", logo[i]);
    }
}

void transicion_SO() {
	MoverCursor(75-31,0);
	const char *logo[] = {
		"                               ..                              ",
		"                           :QBBBBBQQ                           ",
		"                           BBBBQBBBBB                          ",
		"                          .BBBBBBBBBB                          ",
		"              LdZv         BBBBQBBBBB        .UP2:             ",
		"            XBBBBBQ5      vBBBBBBBQBQ.      QBBBBBBi           ",
		"           BBBBBBBBQBs. iZBQBBBBBBBBBBU. .XBBBBBBBBQM          ",
		"          PBBBBBBBBBBBBBQBBBBBBBBBQBBBBBBBBBBBBBBBBBB.         ",
		"          .BBBBBBBBBBBBBBBI:        :IBBBBBBBBBQBBBBB          ",
		"            gBQBBBBBBBBr                uBBBBBBBBBB2           ",
		"             .BQBBBBB:       rBBBZSi      uBBBBBBB             ",
		"              .BBBBP          IBBBBBBBv     BBBBB              ",
		"              JBBQ5             UBBQBBBQ7    QBBB              ",
		"            .PBBBB                QBBBQBBP    BBBBi            ",
		"     7BBBBBQBBBBB                  BBBBBBBs   1BBBBBBBBBBg     ",
		"    rBBBBBBBBBBBB   :X             BBBBBBBQ    BBBBBQBBBQBB    ",
		"    ZBBBBQBBBBBBq   bBB.           BBBBBBBB.   BBBBBBBBBBBB:   ",
		"    PBBBBBQBBBBBK   IBBBX        .BBBBBBBBB    BBBBBQBBBBBB:   ",
		"    .BBBBQBBBBBBB   .BBBBBK:   rQBBQBQBBBBB   :BBBBBBBBBBQB    ",
		"      URBBBBBBBBB.   MBBBBBBBBBBQBBBQBBBBB:    BBBBBQBBBBU     ",
		"             :BBBB    QBBBBBBQBBBBBBBBBBBBB:    KB:            ",
		"              iBBBR    7QBBBBBBBBBBBBBBBBBBBQ                  ",
		"              LQBBBB     rBBBBBQBBBQBBBBBBBBBBq                ",
		"             5BBBBBBB1      .7uS1v:  :BBBBBBQBBBv              ",
		"           7BBBBBBBBBQBq.              LBBBBBBBBBB:            ",
		"          LBBBQBQBBBBBBBQBQUi.   .:r     DBBBBBBBBBB           ",
		"          gBBQBBBBBBBBBBBBBBBBBQBBBQBB:   .BBBBBBI1BBj         ",
		"           DBBBBBBQBD.   vBBBBBBBBBBQBr     rBBB    BB         ",
		"            :BBBBBB.      rBBBBBBBBBB         qBB. LBB         ",
		"              .7i.        :BBBBBQBBBB          .QBBBJ          ",
		"                          :BBBBBBBBBB                          ",
		"                           BBBBBBBBBb                          ",
		"                            XBBBBBQ7                           "
	};
    
    for (int i = 0; i < 33; i++) {
		EsperarMiliSeg(50);
		MoverCursor(75-31,i);
        printf("%s\n", logo[i]);
    }
}


void transicion_banco() {
    const char *logo[] = {
		"                              iBB.                             ",
		"                           rgBBBBBBZi                          ",
		"                       7BBBBBQi  rBBBBBQ7                      ",
		"                   7QBBBQBv    .    .jQBBBQRr                  ",
		"               rQBBBBBJ.      qBBj      .1BBBBBDr              ",
		"           rgBBBBBu.        7BBBQBBi        .5QBBBBEi          ",
		"       iDBBBBBI.            BBd  dBB            :SBQBBBP:      ",
		"   :PBQBBBI:                PBBK7ii                 :PBBQBBq:  ",
		"7QBQBBS.                     idQBBB                     :KBBBBg",
		"BBB                         BB.  BQB                        .BQ",
		"BBB:irJj2UIUIU52I2I252ISI   BBB7vQBP   IX25UI25UI2I2IUIuuY7:rBB",
		"qBQBBBQBBBQBBBBBBBBBBBBBB.   YBBBBr   rBBBBBBBBBBBBBBBBBBBBBBBB",
		"   BBU                         I1                         DQQ  ",
		"   BBQ.::::iii:::::iiiiii77v7r::.irv7vrriiiiii:::i:iii:::.BBB  ",
		"   BBBBBBBBBBBBQBBBBBBBBBBBQBBBBBBBBBQBBBBBBBBBBBBBQBBBBBBBBM  ",
		"       BB1     BBY                            SBQ     bBB      ",
		"       BBS  . .BB7         .........          KBB  .. gBB      ",
		"       BBBBBBBBBQr        .BBBQBBBBBB         JBQBBBBBBBB      ",
		"        DBB  7BB.                              :BBi  BBI       ",
		"        KBB  :BB                                BB   BBY       ",
		"        EBB  iBQ          iBBBBBBQBBB:         .BB.  BBu       ",
		"        dBB  rBB         BBBgr...:rBBBg        .BB.  BBU       ",
		"        ZBB  iBB        ZQB         :BBj       .BQ.  BBu       ",
		"        dBB  rBB        BBE          BQB       .BB.  BB1       ",
		"        ZBB  iBB        BBd          BBB       .BB.  BBj       ",
		"        SBB  :BB        BBE          BBB        BB   BQv       ",
		"        RBB..1BB:       BBZ          BBB       rBB7.:BBq       ",
		"       BBBQBQBBBBv      QBd          BBB      5BBBBBBBBBB      ",
		"       BB1     BBr      BBK          RBQ      5BB     EBB      ",
		"    .. BBX     BBI ...  BBg ........ BBB .... bBB     gBQ  .   ",
		"   BBBBBBBBQBBBBBBBQBBBBBBBBBQBBBBBBBBBBBBBQBBBQBBBBBBBBBQBBB  ",
		"   BBD                                                    QBB  ",
		"   BBX                                                    RBB  ",
		"QBQBBBBBBBBBBBBBBBBBBBQBBBBBBBBBBBBBBBBBBBQBQBBBQBBBBBBBBBBBBBB",
		"BBB.......:.:...:.:...:.:.:.:.:.:...:.:.:.:.:.:.:.:...:.:.. :BB",
		"BBB                                                          BB",
		"gBBBBBBBBBBBBBBBBBBQBBBBBBBBBBBQBQBBBBBBBQBBBBBBBBBBBBBBBQBQBBB"
	};
    
    for (int i = 0; i < 37; i++) {
		EsperarMiliSeg(50);
		MoverCursor(75-31,i);
        printf("%s\n", logo[i]);
    }
}


void transicion_supermercado() {
	MoverCursor(75-31,0);
    const char *logo[] = {
		"                   MBBQB                                       ",
		"                   .. BBr.....:.........                       ",
		"                      rBBBBBBBBBBBBBBBBBB                      ",
		"                      .BZ  ::  i:  i. :Bd                      ",
		"                       BB  BB  BB  BB LBi                      ",
		"                       BB  BB  BB  BB QB                       ",
		"                       5Qi ::  :.  i  BB                       ",
		"                       :BQBBBBBBBBBBBBBZ                       ",
		"                        BB.:i::rrr::i:..                       ",
		"                        dBBBBBBBBBBBBBBBq                      ",
		"                         BB  BB   BB  Bd                       ",
		"         7ssssJYJsJsJYs7rRBBBBQiriBBBQBbr7LvYLLvv7vvLv7        ",
		"        BBQBQBBBBBBBBBQBBBQBBBBBBBBBBBQBQBQBBBBBQQQBQBBB       ",
		"       QBi                                            rBg      ",
		"      1BP                                 5P. IK2I2SS  BQr     ",
		"     .BQ                                                BB     ",
		"     BB.    ....  ....  ....  ....  ....   . .   .      iBB    ",
		"    bQBBBBBBBBBQBBBBBBBBBQBBBBBBBBBBBQBBBBBBBBBBBBBBBBBBBQBL   ",
		"    PB.   gB    BB    BB    QB    BB    BB   .Qg   :B5   rQu   ",
		"    bB.   ZB    BB    BB    BQ    BB    BQ    BP   .Bj   iBJ   ",
		"    ZB.   gB    BB    BB    QB    BB    BB   .Bg   :B5   7BU   ",
		"    .BBg5bBBBggBBQBggBBBBDgBBBBDMBBQBDMBBBBDQBBBBZQBBBP5QBB    ",
		"      7EBBi vggX  vggI  JgDU  IQgs  2MZv .SME7 .KMD7 JBBP7     ",
		"        PB                                           .Bv       ",
		"        DB.  rZBBBBBBBBBBBBg1  SDBBBBBBBQBBBBBBBQg:  iQI       ",
		"        gQ.  BBd5XqKqKPKqIIBB  BB1XKPXqKPXqXqXKUQBQ  iB2       ",
		"        gB.  BB            BB  BQ                Bd  rBS       ",
		"        MB.  BB            BB  BB               :BE  iBI       ",
		"        gB.  BB        SP  BB  BB               .Bb  rBS       ",
		"        MB.  BB        BB  BB  BB                BE  iB2       ",
		"        gB.  BB        bg  BQ  BB:irrrrrrrirrrii2BR  rB5       ",
		"        MB.  QB            BB  BBBBBBBBBBBBBBBBBBBL  iB2       ",
		"        DB.  BB            BB                        iBI       ",
		"        PQ   gB            QB                        .BL       ",
		"  i:::..QB7. BBi.::::::::..BQ..:::.:::::.:.:.:.:.:.:.UBZ.:  ir ",
		" .BBBBBBgbQBBZdRBQBBBBBBBBBbdQBBBQBBBBBBBQBBBQBBBBBBBMEgBB  BQ "
	};

    
    for (int i = 0; i < 36; i++) {
		EsperarMiliSeg(50);
		MoverCursor(75-31,i);
        printf("%s", logo[i]);
    }
}


void mostrarMenu() {
	int y=20;
	imagen_menu();
	MoverCursor(70,y);
    printf("1. Supermercado\n");
	MoverCursor(70,y+2);
    printf("2. Procesos en el sistema operativo\n");
	MoverCursor(70,y+4);
    printf("3. Banco\n");
	MoverCursor(70,y+6);
    printf("4. Salir\n");
	MoverCursor(70,y+8);
    printf("Seleccione una opción: ");
}
