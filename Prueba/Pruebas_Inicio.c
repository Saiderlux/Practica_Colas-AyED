//Compilar: gcc Pruebas_Inicio.c presentacion(win/lin).c -o pruebas

//LIBRERAS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "presentacion.h"

//DEFINICION DE CONSTANTES
#define TIEMPO_BASE	200			//Tiempo base en ms

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
        printf("%s\n", logo[i]);
    }
}

int main(void)
{
	dibujarLogoESCOM();
	return 0;
}