
// Public routine that performs the evaluation. Examines the postfix machine
// to see if a single result is left and if so, return it; otherwise prints
// error.
template<class NumericType>
NumericType Evaluator<NumericType>::getValue( ) {
    
    Tokenizer<NumericType> tok( str );
    Token<NumericType> lastToken;
    
    do {
        lastToken = tok.getToken( );
        processToken( lastToken );
    } while ( lastToken.getType( ) != EOL );
    
    if ( postFixStack.empty( ) ) {
        cerr << "Missing operatnd!" << endl;
        return 0;
    }
    
    NumericType theResult = postFixStack.back( );
    postFixStack.pop_back( );
    if ( !postFixStack.empty( ) )
        cerr << "Warning: missing operators!" << endl;
    
    return theResult;
}

// After token is read, use operator precedence parsing algorithm to process
// it; missing opening parentheses are detected here.
template<class NumericType>
void Evaluator<NumericType>::
processToken( const Token<NumericType> &lastToken ) {
    TokenType topOp;
    TokenType lastType = lastToken.getType( );
    
    switch( lastType ) {
        case VALUE:
            postFixStack.push_back( lastToken.getValue( ) );
            postFixVarStack.push_back( ' ' );
            return;
        case VAR_A:                           //added these straight from the instruction
            postFixStack.push_back( var_a );
            postFixVarStack.push_back( 'a' );
            return;
        case VAR_B:
            postFixStack.push_back( var_b );
            postFixVarStack.push_back( 'b' );
            return;
        case VAR_C:
            postFixStack.push_back( var_c );
            postFixVarStack.push_back( 'c' );
            return;
        case CPAREN:
            while( ( topOp = opStack.back( ) ) != OPAREN &&
                  topOp != EOL ){
                switch (topOp) {   ///this switch statemnt will choose whether is needs to be unary or binary
                    case UN_MINUS:
                        unaryOp(topOp);
                        break;
                    case UN_PLUS:
                        unaryOp( topOp);
                        break;
                    case NOT:
                        unaryOp(topOp);
                        break;
                    case BIT_COMP:
                        unaryOp(topOp);
                        break;
                    default:
                        binaryOp(topOp);
                        break;
                }
            }
            if ( topOp == OPAREN )
                opStack.pop_back( ); // get rid of opening parethesis
            else
                cerr << "Missing open parenthesis" << endl;
            break;
            
        default: // general operator case
            while ( PREC_TABLE[ lastType ].inputSymbol <=
                   PREC_TABLE[ topOp = opStack.back( ) ].topOfStack ){
                
                if(topOp == UN_MINUS || topOp == UN_PLUS
                   || topOp == NOT || topOp == BIT_COMP)   //add unary section so these can work
                    unaryOp( topOp );
                
                else											
                    binaryOp( topOp );			//will jump here if they are not unary
                
                
                
            }
            if ( lastToken.getType( ) != EOL )
                opStack.push_back( lastType );
            break;
    }
}

// Process an operator by taking two items off the postfix stack, applying
// the operator, and pushing the result.
// Print error if missing closing parenthesis or division by 0.
template<class NumericType>
void Evaluator<NumericType>::binaryOp( TokenType topOp ) {
    if ( topOp == OPAREN ) {
        cerr << "Unbalanced parenthss" << endl;
        opStack.pop_back( );
        return;
    }
    
    
    NumericType rhs = getTop( );
    NumericType lhs = getTop( );
    
    
    postFixVarStack.pop_back();
    
    
    char variableHolder = postFixVarStack.back(); //setting a temp variable to hold the character
    postFixVarStack.pop_back();
    
    // the original operators
    if ( topOp == PLUS )
        postFixStack.push_back( lhs + rhs );
    else if ( topOp == MINUS )
        postFixStack.push_back( lhs - rhs );
    else if ( topOp == MULT )
        postFixStack.push_back( lhs * rhs );
    else if ( topOp == DIV )
        if ( rhs != 0 )
            postFixStack.push_back( lhs / rhs );
        else {
            cerr << "Division by zero" << endl;
            postFixStack.push_back( lhs );
        }
    
    // C++ operators
        else if ( topOp == MODULUS )
            postFixStack.push_back( lhs % rhs );
        else if ( topOp == SHIFT_L )
            postFixStack.push_back( lhs << rhs );
        else if ( topOp == SHIFT_R )
            postFixStack.push_back( lhs >> rhs );
        else if ( topOp == LT )
            postFixStack.push_back( lhs < rhs );
        else if ( topOp == LE )
            postFixStack.push_back( lhs <= rhs );
        else if ( topOp == GT )
            postFixStack.push_back( lhs > rhs );
        else if ( topOp == GE )
            postFixStack.push_back( lhs >= rhs );
        else if ( topOp == EQUAL )
            postFixStack.push_back( lhs == rhs );
        else if ( topOp == NOTEQUAL )
            postFixStack.push_back( lhs != rhs );
        else if ( topOp == BIT_AND )
            postFixStack.push_back( lhs & rhs );
        else if ( topOp == BIT_EOR )
            postFixStack.push_back( lhs ^ rhs );
        else if ( topOp == BIT_IOR )
            postFixStack.push_back( lhs | rhs );
        else if ( topOp == LOG_AND )
            postFixStack.push_back( lhs && rhs );
        else if ( topOp == LOG_OR )
            postFixStack.push_back( lhs || rhs );
        //ADDED THE FOLLOWING IF STATEMENT TO HANDLE LETTERS
        else if ( topOp == ASSIGNMENT ){
           if(variableHolder == 'a'){    //checking to see if the temp variable is same as a
                var_a=rhs;
            }
            else if(variableHolder == 'b'){  //checkign to see if the temp variable is the same as b
                var_b = rhs;
            }
            else if(variableHolder == 'c'){  //checking to see if the temp variable is the same as c
                var_c = rhs;
            }

            postFixStack.push_back(rhs);
            
        }
    opStack.pop_back( );
    postFixVarStack.push_back(' ');
}
/* - -----------------------------------------------------------------
  THIS FUNCTION IS ADDED ON SO IT WILL TAKE ON THE UNARY OPERATORS. BIT COMP, UN_PLUS,UN_MINUS, AND NOT
  SIMILAR TO WHAT BINARYOP IS DOING
*/

template<class NumericType>
void Evaluator<NumericType>::unaryOp(TokenType topOp) {
    if ( topOp == OPAREN ) {
        cerr << "Unbalanced parenthesis" << endl;     //USED THE SAME FORMAT FROM BINARYOP
        opStack.pop_back( );
        return;
    }
    NumericType lhs = getTop( ); //ONLY LHS IS NEEDED FOR UNARY OPERATORS
    
    postFixVarStack.pop_back();
    //THE FLLLOWING SWITCH STATEMENTS CHECKS TO SEE WHAT TOPOP SHOULD IS ON THE LEFT HAND SIDE
    switch (topOp) {
        case BIT_COMP:
            postFixStack.push_back( ~lhs );
            break;
        case UN_PLUS:
            postFixStack.push_back( lhs );
            break;
        case UN_MINUS:
            postFixStack.push_back( -lhs );
            break;
        case NOT:
            postFixStack.push_back( !lhs );
            break;
        default:
            break;
    }
    opStack.pop_back( );
    postFixVarStack.push_back(' ');
}

// top and pop the postfix machine stack; return the result.
// If the stack is empty, print an error message.
template<class NumericType>
NumericType Evaluator<NumericType>::getTop( ) {
    if ( postFixStack.empty( ) ) {
        cerr << "Missing operand" << endl;
        return 0;
    }
    
    NumericType tmp = postFixStack.back( );
    postFixStack.pop_back( );
    return tmp;
}
