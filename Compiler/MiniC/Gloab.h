enum TokenGroup
{
	// reserved Keyword

	_NKEY,	
	_INT,_CHAR,_FLOAT,							// 声明时的类型
		_IF, _WHILE,
		_ELSE,
		 _PRINTF,						// 有待加入
		
		// operations
		ASSIGN,							// =
		PLUS,							// + / -	
		MINUS,							// - 
		TIMES,							// * / 
		LOGICAL_NOT,					// !
		LS,								// > / <
		
		
		// interpunctions

		LPARAN,							//{
		RPARAN,							//}
		LBRACE,							//(
		RBRACE,							//)
		 COMMA,							//;
		COLON,                          //,
		
		// complex operations
		/*EQ == NEQ/* != */ /*PLUS_PLUS ++ , MINUS_MINUS -- 
		PLUS_ASSIGN/* +=  MINUS_ASSIGN/* -=  TIMES_ASSIGN/* *=  DIV_ASSIGN/* /= 
		NGT <=  NLT/* >= */ LOGICAL/* &&  LOGICAL_OR/* || */,
		
		// others
		_ID, _NUM,/* _STRING, _CHARACTER, _LABEL, _ERROR, _NONE*/
};