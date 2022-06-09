
/*return values*/
#define SUCCESS 0
#define SIZE_ERROR 1
#define CHAR_ERROR -1

/*Allowed parameters*/
#define MIN_SIZE 2
#define MAX_SIZE 40
#define MIN_CHAR !
#define MAX_CHAR ~

/*
This function print a triangle
1. Input is a character and size of base
2. Check if there are no errors and return SUCCESS, otherwise return the type of error.
3. Output is a triangle(for input ('*', 6)

*
**
***
****
*****
******

*/
int func1(int n, char ch,int _setOffNum);
/*
This function print a up size down right triangle 
1. Input is a character and size of base
2. Check if there are no errors and return SUCCESS, otherwise return the type of error.
3. Output is a triangle(for input ('*', 6)

******
*****
****
***
**
*

*/

int func2(int n, char ch,int _setOffNum);
/*
This function print right triangle and up size down right triangle  
1. Input is a character and size of base
2. Check if there are no errors and return SUCCESS, otherwise return the type of error.
3. Output is a triangle(for input ('*', 6)

*
**
***
****
*****
******
*****
****
***
**
*

*/
int func3(int n, char ch,int _setOffNum);
/*
This function print equilateral triangle 
1. Input is a character and size of base
2. Check if there are no errors and return SUCCESS, otherwise return the type of error.
3. Output is a triangle(for input ('*', 6)

	      * 
	     * * 
 	    * * * 
	   * * * * 
	  * * * * * 
 	 * * * * * * 

*/
int func4(int n, char ch,int _setOffNum);
/*
This function print upsize down equilateral triangle
1. Input is a character and size of base
2. Check if there are no errors and return SUCCESS, otherwise return the type of error.
3. Output is a triangle(for input ('*', 6)

	* * * * * * 
  	 * * * * * 
  	  * * * * 
  	   * * * 
    	    * * 
             * 

*/
int func5(int n, char ch,int _setOffNum);
/*
This function print up and upsize down equilateral triangle
1. Input is a character and size of base
2. Check if there are no errors and return SUCCESS, otherwise return the type of error.
3. Output is a triangle(for input ('*', 6)

	      * 
	     * * 
 	    * * * 
	   * * * * 
	  * * * * * 
 	 * * * * * *
	  * * * * * 
  	   * * * * 
  	    * * * 
  	     * * 
    	      * 
    	      
*/
int func6(int n, char ch,int _setOffNum);
