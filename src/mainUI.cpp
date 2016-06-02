#include <curses.h>
#include <stdlib.h>
#include <string>
#include "../include/windows.h"
#include "../include/def.h"
#include "../include/messenger.h"

int main(){
  /*
    +--------------------------------------------------------------------------------------------+
    |- Lê as funções pressionadas com a função getch.                                            |
    |- Se uma das teclas F1 ou F2 ou F3 é pressionada, desenha a janela de menu correspondente
    |  com a função correspondente ao menu.                                                                           |
    |- Após isto chama a função scrollmenu e deixa o usuário fazer a seleção a partir dos menus. |
    |- Após o retorno da função scrollmenu apaga as janelas de menu e imprime o ítem selecionado |
    |  na barra de mensagem.                                 |
    |- Se a tecla ENTER for pressionada, então o ítem selecionado é retornado.                   |
    |- Se a tecla ESC é pressionada, os menus são fechados.                                      |
    +--------------------------------------------------------------------------------------------+
  */
  int key;
  int itemselecionado;
  WINDOW **itensmenu;
  WINDOW *menu,*mensagem;

  //--------- Verifica se há imagem selecionada
  bool imageSelected = false;

  //--------- Variaveis para o nome da imagem
  /*char fileNameOpenC[200];
  char fileNameSaveC[200];
  std::string fileNameOpen;
  std::string fileNameSave;*/

  //--------- Largura, altura e filtro
  bool color, filtered = false;
	int width, height;

  //--------- Vetores com as camadas de cores
  unsigned char red[MAXH][MAXW], green[MAXH][MAXW], blue[MAXH][MAXW];
  unsigned char filterRed[MAXH][MAXW], filterGreen[MAXH][MAXW], filterBlue[MAXH][MAXW];


  //Inicializações---------------------------------------------
  initscr();      //Inicializando a ncurses
  start_color();  //Tornando o uso das cores possíveis

  //Definição dos pares de cores
  init_pair(1,COLOR_GREEN,COLOR_BLACK);
  init_pair(2,COLOR_BLACK,COLOR_GREEN);
  init_pair(3,COLOR_RED,COLOR_GREEN);

  curs_set(0);  //Faz com que o cursor físico fique invisível.
  noecho();     //Impede que as teclas apareçam na tela
  keypad(stdscr,TRUE);  //Ativa as teclas de função
  //-----------------------------------------------------------

  bkgd(COLOR_PAIR(1));
  menu=subwin(stdscr,1,80,0,0);
  mensagem=subwin(stdscr,1,79,23,1);
  Windows::criarMenu(menu);
  move(2,1);
  printw("Este programa edita imagens com a extensão \".pnm\"");
  move(3,1);
  printw("Para editar uma imagem, siga os passos abaixo:");
  move(4,1);
  printw("1 - Abra o menu Imagem (F1) e selecione a opçcão Abrir Imagem.");
  move(5,1);
  printw("2 - Use os menus Editar(F2) ou Filtros (F3) e aplique o efeito desejado.");
  move(6,1);
  printw("3 - Salve a imagem usando o menu Imagem (F1) com a cor desejada.");
  move(7,1);
  printw("ESC - Encerra o programa.");
  move(12,1);
  printw("Obrigado por utilizar o pnmEditor.");
  move(13,1);
  printw("Desenvolvido por: Lenilson Nascimento e Raphael Carmo.");
  refresh();

  do {
      key=getch();
      werase(mensagem);
      wrefresh(mensagem);
      if (key==KEY_F(1))
      {
          itensmenu=Windows::criarMenuImagem(0);
          itemselecionado=Windows::scrollmenu(itensmenu,3,0);
          if (itemselecionado<0)
              wprintw(mensagem,"Nenhum ítem foi selecionado.");
          else
          {
            /*
            * Se for selecionado o menu abrir imagem chamamos a função loadPNM
            */
            if(itemselecionado+1 == 1)
            {
              Messenger::fileOpen(mensagem,width,height,color,imageSelected,red,green,blue);
            }
            /*
            * Se for selecionado o menu salvar tons de cinza chamamos a função exportP2
            */
            if(itemselecionado+1 == 2)
            {
              Messenger::fileSaveGray(mensagem,width,height,imageSelected,filtered,red,filterRed);
            }

            /*
            * Se for selecionado o menu salvar colorido chamamos a função exportP3
            */
            if(itemselecionado+1 == 3)
            {
              Messenger::fileSaveColor(mensagem,width,height,imageSelected,filtered,red,green,blue,filterRed,filterGreen,filterBlue);
            }
          }
          touchwin(stdscr);
          refresh();
      }
      else if (key==KEY_F(2))
      {
          itensmenu=Windows::criarMenuEditar(20);
          itemselecionado=Windows::scrollmenu(itensmenu,4,20);
          if (itemselecionado<0)
              wprintw(mensagem,"Nenhum ítem foi selecionado");
          else
          {
            if(itemselecionado+1 == 1)
            {
              Messenger::imageLighten(mensagem,width,height,imageSelected,color,red,green,blue);
            }
            if(itemselecionado+1 == 2)
            {
              Messenger::imageMirror(mensagem,width,height,imageSelected,color,red,green,blue);
            }
            if(itemselecionado+1 == 3)
            {
              Messenger::imageNegative(mensagem,width,height,imageSelected,color,red,green,blue);
            }
          }
          touchwin(stdscr);
          refresh();
      }
      else if (key==KEY_F(3))
      {
          itensmenu=Windows::criarMenuFiltros(40);
          itemselecionado=Windows::scrollmenu(itensmenu,5,40);
          if (itemselecionado<0)
              wprintw(mensagem,"Nenhum ítem foi selecionado");
          else
          {
            if(itemselecionado+1 == 1)
            {
              Messenger::filterSobel(mensagem,width,height,imageSelected,color,filtered,red,green,blue,filterRed,filterGreen,filterBlue);
            }
            if(itemselecionado+1 == 2)
            {
              Messenger::imageFilter(mensagem,"gb",width,height,imageSelected,color,filtered,red,green,blue,filterRed,filterGreen,filterBlue);
            }
            if(itemselecionado+1 == 3)
            {
              Messenger::imageFilter(mensagem,"bo",width,height,imageSelected,color,filtered,red,green,blue,filterRed,filterGreen,filterBlue);
            }
            if(itemselecionado+1 == 4)
            {
              Messenger::imageFilter(mensagem,"la",width,height,imageSelected,color,filtered,red,green,blue,filterRed,filterGreen,filterBlue);
            }
            if(itemselecionado+1 == 5)
            {
              Messenger::imageFilter(mensagem,"fo",width,height,imageSelected,color,filtered,red,green,blue,filterRed,filterGreen,filterBlue);
            }
          }
          touchwin(stdscr);
          refresh();
      }
  } while (key!=ESCAPE);

  delwin(menu);
  delwin(mensagem);
  endwin();
  return 0;
