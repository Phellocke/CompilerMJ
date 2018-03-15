

TranslationUnit = 	{ [ "extern" ] TypeSpecifier, identifier, 
						  ( "[", integer, "]" ] }, ";"
						| "(", [ Parameter, { ",", Parameter } ], ")",
					   	  ( CompoundStatement |";")
					    )
					}
				;
TypeSpecifier 	=	{ '*' }
				|   "void"
				|	"byte"
				|	"float"
				;