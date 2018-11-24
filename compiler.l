%{
#include <string.h>
#include "label.h"
#include "error_handler.h"
#include "compiler.tab.h"	//tokens
%}
%x comment_block
%%

"["									BEGIN(comment_block);	
<comment_block>[("*/")]*						/* ignore */
<comment_block>"]"							BEGIN(INITIAL);

[0-9]+	{ yylval.intval = atoi(yytext);
			return(NUMBER);		}
IN	{ return(_IN);		}

DECLARE	{ return(DECLARE);			}
\+	{ return(PLUS);			}
-	{ return(MINUS);			}
\/	{ return(DIV);			}
\%	{ return(MOD);			}
\*	{ return(TIMES);			}
==	{ return(EQ);		}
!=	{ return(DIFF);		}
\<=	{ return(LE);		}
\>=	{ return(GE);		}
\<	{ return(LEQ);		}
\>	{ return(GEQ);		}
:=	{ return(ASSGNOP);		}
IF		{ return(IF);			}
THEN	{ return(THEN);			}
FROM	{ return(FROM);			}
ENDFOR		{ return(ENDFOR);}
ENDWHILE		{ return(ENDWHILE);			}
END\nEND { yyerror("\"END\" error");}

END		{ return(END);			}
ENDIF		{ return(ENDIF);			}
ELSE	{ return(ELSE);			}
WHILE	{ return(WHILE);		}
DOWNTO	{ return(DOWNTO);}
DO		{ return(DO);			}
ENDDO		{ return(ENDDO);			}
READ	{ return(GET);			}
WRITE	{ return(PUT);		}
FOR     {return(FOR); }
TO     {return(TO); }

[_a-z]+	{ yylval.id = (char*) strdup(yytext);
			return(IDENTIFIER);	}

[ \t]+
\n		{ lines++;				}
.		{ return(yytext[0]);	}
%%
int yywrap(void){}
