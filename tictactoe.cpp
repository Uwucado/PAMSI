#include <iostream>
#include <vector>


using namespace std;



template <int ROZMIAR,int ZNAKI> 
class Board
{
 public:
  char board[ROZMIAR][ROZMIAR];
public:
  void Wypisz_plansze();
  Board();
  bool Pelna_plansza();
  bool Zakonczona_gra();
  int CzyWygrana ();
  int minimax(int depth,char marker);
  pair<int,int> Optymalny_ruch();
};


template <int ROZMIAR,int ZNAKI>
Board<ROZMIAR,ZNAKI>::Board() 
{
for(int a=0; a<ROZMIAR;a++)
    {
      for(int b=0; b<ROZMIAR;b++)
	{
	  board[a][b]='-';
	}

    }
}

template <int ROZMIAR,int ZNAKI>
class Winning
{
public:
  vector<vector<pair<int, int>>> wygrywajace_kombinacje;
  Winning();
};

template <int ROZMIAR,int ZNAKI>
Winning<ROZMIAR,ZNAKI>::Winning() 
{
  
  vector<pair<int, int>> Wektor_posredni;

  for(int k=0;k<ROZMIAR;k++)
    {
      
      for(int j=0;j+ZNAKI<=ROZMIAR;j++)
	{
	  Wektor_posredni.clear();
	  for(int l=j; l < ZNAKI+j; l++)
	    {
	      Wektor_posredni.push_back(make_pair(k, l));
	    }
	  wygrywajace_kombinacje.push_back(Wektor_posredni);
	  
	}
      
    }

  
  for(int k=0;k<ROZMIAR;k++)
    {
      
      for(int j=0;j+ZNAKI<=ROZMIAR;j++)
	{
	  Wektor_posredni.clear();
	  for(int l=j; l < ZNAKI+j; l++)
	    {
	      Wektor_posredni.push_back(make_pair(l, k));
	    }
	  
	  wygrywajace_kombinacje.push_back(Wektor_posredni);
	  
	}
      
    }

   
  for(int k=0;k<=ROZMIAR-ZNAKI;k++)
    {
      
      for(int j=0;j<=ROZMIAR-ZNAKI;j++)
	{
	  Wektor_posredni.clear();
	  for(int l=0; l < ZNAKI; l++)
	    {
	      Wektor_posredni.push_back(make_pair(k+l, j+l));
	    }
	   
	  wygrywajace_kombinacje.push_back(Wektor_posredni);
	  
	}
      
      
    }
   for(int k=ROZMIAR-1; k-ZNAKI+1>=0;k--)
    {
      
      for(int j=0;j<=ROZMIAR-ZNAKI;j++)
	{
	  Wektor_posredni.clear();
	  for(int l=0; l < ZNAKI; l++)
	    {
	      Wektor_posredni.push_back(make_pair(k-l, j+l));
	    }
	  
	  wygrywajace_kombinacje.push_back(Wektor_posredni);
	  
	}
    }
   cout << endl;
};

template <int ROZMIAR, int ZNAKI>
Winning<ROZMIAR,ZNAKI> Wygrywajace_stany;

template <int ROZMIAR, int ZNAKI> 
void Board<ROZMIAR,ZNAKI>::Wypisz_plansze()
{
  
	cout << endl;
	for(int i=0;i<ROZMIAR;i++)
	  {
	    cout << '|';
	    for(int j=0;j<ROZMIAR;j++)
	      {
		
		cout << board[i][j] << " | " ;
	      }
	    cout << endl;
	    for (int q=0;q<ROZMIAR;q++)
		     {
		       cout  << "----";
		     }
	    cout << endl;
	      }
}

template <int ROZMIAR, int ZNAKI> 
bool Board<ROZMIAR,ZNAKI>::Pelna_plansza()
{
  int Ruchy=0;
  for(int o=0; o<ROZMIAR ; o++)
    {
      for(int h=0; h<ROZMIAR ; h++)
	{
	  if(board[o][h]=='-'){Ruchy=1;}
	}
    }
	
	if (0 == Ruchy)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template <int ROZMIAR, int ZNAKI>
int Board<ROZMIAR,ZNAKI>::CzyWygrana ()
{
  int Str=0;
  int Str2=0;
  for(int i=0; i<Wygrywajace_stany<ROZMIAR,ZNAKI>.wygrywajace_kombinacje.size() ; i++)
    {
      Str=0;
      Str2=0;
      
      for(int j=0; j<ZNAKI; j++)
	{
	  if(board[Wygrywajace_stany<ROZMIAR,ZNAKI>.wygrywajace_kombinacje[i][j].first][Wygrywajace_stany<ROZMIAR,ZNAKI>.wygrywajace_kombinacje[i][j].second] == 'X')
	  {
	    Str++;
	  }
	  
	}
       for(int j=0; j<ZNAKI; j++)
	{
	  if(board[Wygrywajace_stany<ROZMIAR,ZNAKI>.wygrywajace_kombinacje[i][j].first][Wygrywajace_stany<ROZMIAR,ZNAKI>.wygrywajace_kombinacje[i][j].second] == 'O')
	  {
	    Str2++;
	  }
	  
	}
      
     
      	  if(Str == ZNAKI)
	    {
		 return -1;
	    }
	  if(Str2 == ZNAKI)
	    {
	      return 1;
	    }
      
    }
  
  return 0;
}

template <int ROZMIAR,int ZNAKI>
int Board<ROZMIAR,ZNAKI>::minimax(int depth,char marker)
{
  int score = CzyWygrana();
  if(score == (-1)){return score;}
  if(score == 1){return score;}
  if(Pelna_plansza()){return 0;}
  
  if(marker == 'O')
    {
      int best = -10;
      for(int i=0; i<ROZMIAR; i++)
	{
	  for(int j=0; j<ROZMIAR ; j++)
	    if(board[i][j] == '-')
	      {
		board[i][j] = 'O';
		
		  
		best = max(best,minimax(depth+1,'X'));
		  
		board[i][j] = '-';
	      }
	}
      return best;
    }
      
    
    else
    {
      int best = 10;
       for(int i=0; i<ROZMIAR; i++)
	{
	  for(int j=0; j<ROZMIAR ; j++)
	    if(board[i][j] == '-')
	      {
		board[i][j] = 'X';
		
		  
		best = min(best,minimax(depth+1,'O'));
		  
		board[i][j] = '-';
	      }
	}
      return best;
    }

}
template <int ROZMIAR,int ZNAKI>
pair<int,int> Board<ROZMIAR,ZNAKI>::Optymalny_ruch()
{
  int bestVal=-100;
  pair<int,int> Najlepszy_ruch = make_pair(-1,-1);
  
  for(int k=0; k<ROZMIAR;k++)
    {
      for(int l=0; l<ROZMIAR ; l++)
	{
	  if(board[k][l]=='-')
	    {
	      board[k][l] = 'O';
	      int Wartosc = minimax(0,'X');
	      board[k][l] = '-';
	      
	       if(Wartosc > bestVal)
		 {
		   Najlepszy_ruch.first = k;
		   Najlepszy_ruch.second = l;
		   bestVal=Wartosc;
		 }
	    }
	}
    }
  return Najlepszy_ruch;
}

template <int ROZMIAR, int ZNAKI> 
bool Board<ROZMIAR,ZNAKI>::Zakonczona_gra()
{
  
  int Wynik = CzyWygrana();
  if (Pelna_plansza()  && Wynik == 0)
	{
	  cout << "OSIAGNIETO REMIS" << endl;
		return true;
	}
  
  
	  if(Wynik==(-1))
	    {
	      cout << "WYGRYWA GRACZ" << endl;
	      return true;
	    }
	  if(Wynik==(1))
	    {
	      cout << "WYGRYWA AI" << endl;
	    
	      return true;
	    }	

  return false;
  
}


int main()
{
  int const ROZMIAR = 3;
  int const ZNAKI = 3;
  Board<ROZMIAR,ZNAKI> boarded ;

	boarded.Wypisz_plansze();

	while (!boarded.Zakonczona_gra())
	{

	  
		int a, b;
		cout << "Wiersz(Liczymy od 0): ";
		cin >> a;
		cout << "Kolumna(Liczymy od 0): ";
		cin >> b;
		cout << endl << endl;
		
		while (boarded.board[a][b] != '-')
		{
		  
		  cout << "Pozycja (" << a << ", " << b << ") jest zajeta!" << endl;
		  cout << "Wiersz(Liczymy od 0): ";
		  cin >> a;
		  cout << "Kolumna(Liczymy od 0): ";
		  cin >> b;
		  cout << endl;
		}
	       
		  boarded.board[a][b] = 'X';
		
		if(boarded.Zakonczona_gra())
		  {
		    boarded.Wypisz_plansze();
		    break;
		  }
		pair<int, int> ai_move = boarded.Optymalny_ruch();

		boarded.board[ai_move.first][ai_move.second] = 'O';

		boarded.Wypisz_plansze();
		
	}
	return 0;

}
