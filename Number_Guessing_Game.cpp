// Number guessing game
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<limits>
using namespace std;
int main()
{ 
	srand(time(0));
	int cguess,uguess,choice,n=1;
	cout<<" Welcome to NUMBER-GUESSING-GAME"<<endl;
	cout<<"Rules:\n >You need to guess a number between 1 and 100.\n >You will be given 3 TRIES and after that the GAME will OVER\n >If you guess the umber right ,you WIN."<<endl;
	
	
	
    do{
		n=1;
		cguess=rand()%100+1;  //generate a Random Number
		while(n<=3){            
			cout<<"\n\tTRY "<<n<<":"<<endl;
			
			while(true){                //inputing till user enter a valid input
				cout<<"Enter a number (between 1 an 100) = ";
				cin>>uguess;
			
				if(cin.fail()){
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout<<"Not a digit!!"<<endl;
				}
				else if (uguess<1 || uguess>100){
					cout<<"Not a digit btw 1 and 100!!"<<endl;
				}
				else{
					break;
				}
			}
			

			if(cguess==uguess){
				cout<<"You and Computer both guessed "<<cguess<<endl;
				cout<<"yahoooo ! You WIN!!!"<<endl;
				break;
			}
			else if(cguess>uguess){
				cout<<"Your guessed number is too Low!!"<<endl;
			}
			else if(cguess<uguess){
				cout<<"Your guessed number is too High!!"<<endl;
			}
			else{
				cout<<"Some Problem occured!!."<<endl;
			}
			n++;
		}
		if(cguess!=uguess){
		cout<<"You've used all your tries! The correct Number was "<<cguess<<endl;
		}
		while(true){
			cout<<"\nYou want to play again?\n  1.Yes \n  2.No"<<endl;           //Restarting game if usr wants
			cin>>choice; 

			if(cin.fail()){
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout<<"Invalid Input!!"<<endl;
				}
				else if (choice<1 || choice>2){
					cout<<"Invalid Input!!"<<endl;
				}
				else{
					break;
				}
		}
		
	   }while(choice!=2);

	cout<<"\t\tGame End."<<endl;
	return 0;
}