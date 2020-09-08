/****************************************************************/
/*                  RPN Calculator Driver File                  */
/****************************************************************/
/*      TODO: Implement driver as described in the writeup      */
/****************************************************************/

#include "RPNCalculator.hpp"
#include <iostream>
#include <ctype.h>
using namespace std;

bool isNumber(string s)
{
    if(s.size() == 1 && s == "-") return false;
    else if(s.size() > 1 && s[0] == '-') s = s.substr(1);

    bool point = false;
    for(int i = 0; i < s.size(); i++)
    {
      if(!isdigit(s[i]) && s[i] != '.') return false;
      if(s[i]=='.' and !point) point = true;
      else if(s[i]=='.' and point) return false;
    }

    return true;
}

RPNCalculator :: RPNCalculator()
{
  stackHead = NULL;
}

RPNCalculator :: ~RPNCalculator()
{
    if(stackHead == NULL)
    {
        return;
    }
    Operand* ptr = stackHead;
    while(ptr != NULL)
    {
      Operand * temp = stackHead;
      stackHead = stackHead -> next;
      free(temp);
      ptr = ptr->next;
    }
}
bool RPNCalculator :: isEmpty()
{
  if(stackHead == NULL)
  {
    return true;
  }
  else
  {
    return false;
  }

}
void RPNCalculator ::  push(float num)
{
  Operand* temp = new Operand(); 
  temp -> number = num; 
  Operand* temphead = stackHead; 
  stackHead = temp;
  stackHead -> next = temphead; //previous head
}

void RPNCalculator :: pop()
{
    if(stackHead == NULL)
    {
        cout<<"Stack empty, cannot pop an item."<<endl; 
        return;
    }
    
    Operand * temp = stackHead;
    stackHead = stackHead -> next;
    free(temp);
}

Operand* RPNCalculator ::  peek()
{
  if(stackHead == NULL)
  {
    cout<<"Stack empty, cannot peek."<<endl;
  }
  return stackHead;
}
bool RPNCalculator :: compute(std::string symbol)
{
  if (symbol != "+" && symbol != "*")
  {
    cout<<"err: invalid operation"<<endl; 
    return false;
  }
  else 
  {
    float first, second, result;
    if (isEmpty())
    {
      cout<<"err: not enough operands"<<endl;
      return false; 
    }
    Operand* topnode = peek();
    first = topnode->number;
    pop();
    if (isEmpty())
    {
      cout<<"err: not enough operands"<<endl;
      push(first);
      return false; 
    }
    topnode = peek();
    second = topnode->number;
    pop(); 
    if (symbol == "+")
    {
      result = first + second;
      push(result); 
    }
      if (symbol == "*")
    {
      result = first * second;
      push(result); 
    }
    
    //cout<<result<<endl;
    return true;
  }
  return false;
}


int main()
{
  
  //RPNCalculator rpn;
  //rpn.push(1.5);
  //rpn.push(2.1);
  //float x = rpn.compute("*");
  //cout<<x<<endl;
  
  
  // TODO - Declare a stack to hold the operands
  RPNCalculator rpn;
  string input;

  cout << "Enter the operators and operands ('+', '*') in a postfix format" << endl;

  while(true)
  {
    string input;
    cout << "#> ";
    getline(cin, input);

    if(input == "*" || input == "+")
    {
      rpn.compute(input); //partial expression because they have not entered = sign yet
    }
    else if (input == "=")
    {
      break;
    }
    else
    {
      if (isNumber(input))
      
      {
        float num = stod(input);
        rpn.push(num);
      }
    }
  } //end of while


  if(rpn.isEmpty())
  {
    cout<< "No operands: Nothing to evaluate"<<endl;
    return 0;
  }


  
  //is the expression invalid - we need 2 numbers to add or muliply
  Operand* topnode = rpn.peek();
  float result = topnode->number;
  //cout << result << endl;
  rpn.pop();
  if (rpn.isEmpty())
  {
    cout<<result<<endl;
  }
  else
  {
    cout<<"Invalid expression"<<endl;
  }
  return 0;

  

}

