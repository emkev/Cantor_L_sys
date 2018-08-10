
/* 26 Jan 2018 start coding .
   Cantor expression for L-system mode with C Language .
   Original Inspiration from the Flight's Business Class . 
*/


#include <stdio.h>
#include <stdlib.h>


int Generations = 4 ; // generations of running
int strMaxLen = 81 ;  // set to times number for 3.  (3)^(Generations) 
char str[81+1] ;      // the main string
int lineMaxLen = 81 ;

int ruleNum = 2 ;    // quantity for rule 
int ruleMaxLen = 4 ; // previous item plus next items
char ruleSet[2][4] ; // ruleNum times ruleMaxLen 
char mappingRes[3] ; // Quantity of next items of rule minus 1 .



/*  Function "showChar" :
    Display L-sys Characters By Cantor rules.
 */
void showChar() {

  int a ; 
  for(a = 0 ; a < strMaxLen+1 ; a++) {
    printf("%c" , str[a]);
  }
  printf("\n");

}


/*
   Function "showLine" :
   Display the Cantor Line .
*/
void showLine() {

  int x , y , z ;
  int m ;
  int CharCount = 0 ;
  int UnitLine = 0 ;

  // count all valid Characters
  for(x = 0 ; x < strMaxLen ; x++) {
    if(str[x] != ' ' && str[x] != '\\' )
      CharCount++ ;
  }

  if(CharCount > 0) {

    /*  set "UnitLine" to be a Unit length for Drawing. */
    // line max length could be set a value lonely.
    UnitLine = lineMaxLen / CharCount ;

    for(m = 0 ; m < strMaxLen ; m++) {

      // char 'a' === a Line
      if(str[m] == 'a') {
        for(z = 0 ; z < UnitLine ; z++)
          printf("-");
      }
      // char 'b' === a Empty Position
      else if (str[m] == 'b') {
        for(y = 0 ; y < UnitLine ; y++)
          printf(" ");
      }
      else if (str[m] == '\\') {
        break;
      }      
      else {
        break ;
      }
    }
    printf("\n");
  }
  else {
    printf("non char\n");
  }

}



void MakeRuleSet() {

  /* Please make sure the length of each rule same .
     A array factor for non-value need to be set to empty char .
   */
  
  // Rule 1 :   a ==> aba
  
  ruleSet[0][0] = 'a' ; // one previous item
  
  ruleSet[0][1] = 'a' ; // first  next-item 
  ruleSet[0][2] = 'b' ; // second next-item
  ruleSet[0][3] = 'a' ; // third  next-item

  // Rule 2 :   b ==> bbb
  
  ruleSet[1][0] = 'b' ;
  
  ruleSet[1][1] = 'b' ;
  ruleSet[1][2] = 'b' ;
  ruleSet[1][3] = 'b' ;

}



/*
   Function "doRule" :
   Try to match rules for the char .
*/
int doRule(char prs) {

  int a , b , c ;

  // make sure Dataset mappingRes clear before using
  for(c = 0 ; c < ruleMaxLen-1 ; c++) {
    mappingRes[c] = ' ' ;
  }

  // loop to find a valid rule  
  for(a = 0 ; a < ruleNum ; a++) {

    // when found a matching rule for current char
    if( prs == ruleSet[a][0] ) {
      for(b = 1 ; b < ruleMaxLen ; b++)
        mappingRes[b-1] = ruleSet[a][b] ;
      return 1 ;
    } 

  } // for(a = 0 ; a < ruleNum ; a++) : end loc

  
  return 0 ;  // no found any matching rule

}




void generate() {

  int x , y , z ;
  int m , n ;
  int isTransfer = 0 ;
  char strTmp[100] ;
  int pos = 0 ;


  // Ready for a Double Pitches Exchanging System
  for(m = 0 ; m < strMaxLen+1 ; m++) {
    strTmp[m] = ' ' ;
  }


  for (x = 0 ; x < strMaxLen+1 ; x++) {

  	// Exit looping once meeting '\' 
  	if(str[x] == '\\')
      break;
  	

  	isTransfer = 0 ;
  	
    // Try to match rules for current char
    isTransfer = doRule(str[x]) ;
    
    /* found matching rule .
       Append a finding ResultSet to the Temp String DataSet.
     */
    if( isTransfer == 1 ) {

      for(y = 0 ; y < ruleMaxLen-1 ; y++) {
        // the valid results be ended by empty char.
        if(mappingRes[y] != ' ') {
          strTmp[pos] = mappingRes[y] ;
          pos++ ;
        }
        else {
          break ;
	    }
      } // for(y = 0 ; y < ruleMaxLen-1 ; y++) : end loc

    } // if( isTransfer == 1 ) : end Loc
    else {
      strTmp[pos] = str[x] ;
      pos++ ;
    }
    
  } // for(x = 0 ; x < strMaxLen ; x++) : end loc
  

  // Double Pitches to be exchanged
  for(n = 0 ; n < pos ; n++)
    str[n] = strTmp[n] ;

  str[pos] = '\\' ;
  
  
}



int main() {

  int m , n , p ;

  // init :
  str[0] = 'a' ;
  str[1] = '\\' ;
  for(m = 2 ; m < strMaxLen+1 ; m++) {
    str[m] = ' ' ;
  }
  

  showLine();

  // set all rules
  MakeRuleSet();


  // Generate by steps 
  for(n = 0 ; n < Generations ; n++) {
    generate();
    //showChar();
    showLine();
  }
  
  printf("finish\n");

}

