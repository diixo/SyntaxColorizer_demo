// SyntaxColorizer.cpp: implementation of the CSyntaxColorizer class.
//
// Version:	1.0.0
// Author:	Jeff Schering jeffschering@hotmail.com
// Date:	Jan 2001
// Copyright 2001 by Jeff Schering
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SyntaxColorizer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSyntaxColorizer::CSyntaxColorizer()
{
	createDefaultCharFormat();
	SetCommentColor(CLR_COMMENT);
	SetStringColor(CLR_STRING);
	createTables();
	m_pskKeyword = NULL;
	createDefaultKeywordList();
}

CSyntaxColorizer::~CSyntaxColorizer()
{
	ClearKeywordList();
	deleteTables();
}

//////////////////////////////////////////////////////////////////////
// Member Functions
//////////////////////////////////////////////////////////////////////
void CSyntaxColorizer::createDefaultCharFormat()
{
	m_cfDefault.dwMask = CFM_CHARSET | CFM_FACE | CFM_SIZE | CFM_OFFSET | CFM_COLOR;
	m_cfDefault.dwMask ^= CFM_ITALIC ^ CFM_BOLD ^ CFM_STRIKEOUT ^ CFM_UNDERLINE;
	m_cfDefault.dwEffects = 0;
	m_cfDefault.yHeight = 200; //10pts * 20 twips/point = 200 twips
	m_cfDefault.bCharSet = ANSI_CHARSET;
	m_cfDefault.bPitchAndFamily = FIXED_PITCH | FF_MODERN;
	m_cfDefault.yOffset = 0;
	m_cfDefault.crTextColor = CLR_PLAIN;
	strcpy(m_cfDefault.szFaceName,"Courier New");
	m_cfDefault.cbSize = sizeof(m_cfDefault);

	m_cfComment = m_cfDefault;
	m_cfString = m_cfDefault;
}

void CSyntaxColorizer::createDefaultKeywordList()
{
   LPTSTR sKeywords = 
      "a,"
      "able,"
      "about,"
      "above,"
      "across,"
      "after,"
      "again,"
      "all,"
      "along,"
      "also,"
      "although,"
      "always,"
      "among,"
      "an,"
      "and,"
      "another,"
      "any,"
      "anytime,"
      "apart,"
      "apparent,"
      "are,"
      "around,"
      "as,"
      "at,"
      "away,"
      "because,"
      "before,"
      "behind,"
      "being,"
      "below,"
      "besides,"
      "between,"
      "beyond,"
      "both,"
      "but,"
      "by,"
      "can,"
      "could,"
      "down,"
      "each,"
      "either,"
      "even,"
      "evident,"
      "except,"
      "explicit,"
      "farther,"
      "farthest,"
      "few,"
      "fewer,"
      "for,"
      "forever,"
      "from,"
      "furthermore,"
      "here,"
      "him,"
      "his,"
      "however,"
      "i,"
      "if,"
      "in,"
      "indeed,"
      "instead,"
      "into,"
      "is,"
      "it,"
      "its,"
      "just,"
      "less,"
      "like,"
      "lot,"
      "me,"
      "might,"
      "more,"
      "moreover,"
      "most,"
      "my,"
      "never,"
      "nope,"
      "not,"
      "obvious,"
      "of,"
      "off,"
      "often,"
      "on,"
      "once,"
      "one,"
      "only,"
      "onto,"
      "or,"
      "other,"
      "our,"
      "out,"
      "over,"
      "overall,"
      "rather,"
      "self,"
      "several,"
      "she,"
      "should,"
      "so,"
      "soon,"
      "still,"
      "such,"
      "suchlike,"
      "that,"
      "the,"
      "their,"
      "them,"
      "than,"
      "then,"
      "there,"
      "therefore,"
      "these,"
      "they,"
      "thine,"
      "this,"
      "those,"
      "through,"
      "throughout,"
      "thus,"
      "to,"
      "too,"
      "towards,"
      "under,"
      "unless,"
      "until,"
      "up,"
      "upon,"
      "very,"
      "via,"
      "we,"
      "what,"
      "whatever,"
      "which,"
      "while,"
      "will,"
      "with,"
      "within,"
      "without,"
      "would,"
      "yet,"
      "you,"
      "your,"
      "yours"
;

LPTSTR sDirectives = 
   "some,"
   "because,"
   "few,"
   "most,"
   "thus,"
   "thereby,"

   "many,"
   "much,"

   "sooner,"
   "during,"
   "time,"
   "day,"
   "current,"

   "forward,"
   "backward,"

   "free,"
   "well,"

   "further,"
   "matter,"
   "varied,"
   "preferably,"

   "beside,"
   "near,"
   "far,"
   "whole,"
   "nearby,"
   "alongside,"
   "except,"
   "aside,"
   "against,"
   "compared,"
   "versus,"
   "nearly,"
   "roughly,"
   "something,"
   "someone,"
   "somewhat,"
   "anything,"


   "itself,"
   "myself,"
   "yourself,"
   "himself,"
   "herself,"
   "oneself,"
   "themselves,"
   "yourselves,"
   "ourselves,"

   "entire,"
   "entirely,"
   "especially,"
   "everything,"
   "general,"
   "generally,"
   "finally,"
   "largely,"
   "every,"
   "mainly,"
   "mostly,"
   "chiefly,"

   "real,"
   "fact,"
   "effect,"

   "principally,"
   "really,"
   "typically,"
   "usually,"
   "probably,"

   "actually,"
   "truly,"
   "eventually,"
   "full,"
   "total,"

   "according,"
   "accordingly,"
   "respectively,"
   "big,"
   "biggest,"
   "bigger,"
   "various,"

   "nothing,"
   "thing,"
   "nobody,"
   "common,"
   "commonly,"
   "usual,"
   "normal,"
   "normally,"
   "regular,"
   "regularly,"

   "forevermore,"
   "evermore,"
   "everywhere,"
   "anywhere,"
   "somewhere,"
   "endlessly,"
   "timelessly,"
   "apparently,"
   "obviously,"
   "doubtless,"
   "doubtlessly,"

   "partially,"
   "partly,"
   "fully,"
   "wholly,"

   "merely,"
   "simply,"
   "recent,"
   "recently,"
   "lately,"
   "newly,"
   "respectively,"
   "low,"
   "high,"
   "ideally,"

   "opposed,"
   "contrast,"
   "opposite,"

   "inside,"
   "outside"
;

   LPTSTR sVerbsContext = 
"accept,"
"account,"
"accuse,"
"achieve,"
"act,"
"add,"
"agree,"
"analyze,"
"answer,"
"appear,"
"apply,"
"approve,"
"argue,"
"arrive,"
"ask,"
"back,"
"be,"
"become,"
"begin,"
"believe,"
"belong,"
"blame,"
"bleed,"
"blow,"
"borrow,"
"break,"
"bring,"
"build,"
"bump,"
"burn,"
"buy,"
"calculate,"
"call,"
"care,"
"cast,"
"catch," 
"change,"
"cheat,"
"check,"
"choose,"
"close,"
"come,"
"comment,"
"compare,"
"complain,"
"concentrate,"
"congratulate,"
"connect,"
"consent,"
"consist,"
"continue,"
"contribute,"
"correspond,"
"count,"
"create,"
"cross,"
"cut,"
"dedicate,"
"define,"
"depart,"
"depend,"
"desire,"
"detect,"
"devote,"
"disagree,"
"discover,"
"do,"
"draw,"
"dream,"
"drink,"
"drive,"
"drop,"
"eat,"
"enjoy,"
"equip,"
"evaluate,"
"excuse,"
"execute,"
"expect,"
"explain,"
"fall,"
"feel,"
"fill,"
"find,"
"finish,"
"fit,"
"forget,"
"forgive,"
"force,"
"get,"
"give,"
"go,"
"graduate,"
"grow,"
"happen,"
"have,"
"hear,"
"help,"
"hint,"
"hold,"
"hope,"
"hurt,"
"include,"
"increase,"
"inform,"
"ignore,"
"insist,"
"interrupt,"
"intersect,"
"introduce,"
"invest,"
"investigate,"
"invite,"
"judge,"
"jump,"
"keep,"
"knock,"
"know,"
"lag,"
"laugh,"
"lead,"
"learn,"
"leave,"
"lend,"
"let,"
"listen,"
"live,"
"long,"
"look,"
"make,"
"manage,"
"mark,"
"may,"
"meet,"
"memorize,"
"mix,"
"move,"
"name,"
"need,"
"object,"
"observe,"
"offer,"
"open,"
"organize,"
"owe,"
"pass,"
"pay,"
"pick,"
"point,"
"prefer,"
"prepare,"
"prevent,"
"print,"
"promise,"
"propose,"
"provide,"
"pull,"
"push,"
"put,"
"raise,"
"reach,"
"read,"
"recognize,"
"refuse,"
"rely,"
"remember,"
"remind,"
"remove,"
"replace,"
"report,"
"require,"
"resolve,"
"response,"
"retrieve,"
"return,"
"rise,"
"run,"
"save,"
"say,"
"schedule,"
"search,"
"see,"
"send,"
"set,"
"shout,"
"show,"
"sleep,"
"solve,"
"sort,"
"speak,"
"spend,"
"stand,"
"start,"
"stay,"
"stick,"
"stop,"
"support,"
"switch,"
"take,"
"talk,"
"teach,"
"tell,"
"test,"
"thank,"
"think,"
"throw,"
"touch,"
"translate,"
"train,"
"try,"
"turn,"
"understand,"
"use,"
"vote,"
"wait,"
"want,"
"warm,"
"warn,"
"watch,"
"wish,"
"wonder,"
"work,"
"worry,"
"write"
;

LPTSTR sVerbsExtended = 
"activate,"
"add,"
"affect,"
"approve,"
"argue,"
"arrange,"
"arrive,"
"assume,"
"attach,"
"attend,"
"avoid,"
"bind,"
"bound,"
"cancel,"
"categorize,"
"cause,"
"clarify,"
"classify,"
"clean,"
"clear," 
"collect,"
"commit,"
"complete,"
"compose,"
"compute,"
"confuse,"
"conside,"
"construct,"
"consume,"
"contain,"
"contribute,"
"control,"
"converge,"
"correct,"
"correlate,"
"cost,"
"damage,"
"decide,"
"declare,"
"decode,"
"delete,"
"deliver,"
"demonstrate,"
"descend,"
"describe,"
"detect,"
"develop,"
"disable,"
"disconnect,"
"discuss,"
"display,"
"distribute,"
"enable,"
"enter,"
"escape,"
"estimate,"
"evaluate,"
"exemplify,"
"explore,"
"extend,"
"extract,"
"fail,"
"fix,"
"focus,"
"follow,"
"form,"
"fund,"
"gain,"
"group,"
"guide,"
"hide,"
"imagine,"
"implement,"
"imply,"
"impress,"
"improve,"
"indicate,"
"influence,"
"inject,"
"insert,"
"inspect,"
"intend,"
"interact,"
"interest,"
"interpret,"
"introduce,"
"invent,"
"involve,"
"lead,"
"leave,"
"lift,"
"limit,"
"locate,"
"loss,"
"manipulate,"
"mean,"
"mention,"
"miss,"
"mistake,"
"modify,"
"multiply,"
"notice,"
"offer,"
"operate,"
"optimize,"
"perform,"
"place,"
"play,"
"post,"
"predict,"
"present,"
"proceed,"
"process,"
"produce,"
"progress,"
"project,"
"promote,"
"prove,"
"rate,"
"reach,"
"react,"
"realize,"
"receive,"
"recommend,"
"reduce,"
"refer,"
"reflect,"
"relate,"
"release,"
"remain,"
"repair,"
"repeat,"
"represent,"
"request,"
"research,"
"respond,"
"return,"
"satisfy,"
"select,"
"separate,"
"serve,"
"share,"
"specialize,"
"spend,"
"study,"
"submit,"
"suggest,"
"sum,"
"summarize,"
"supply,"
"sure,"
"trace,"
"track,"
"transfer,"
"transit,"
"transmit,"
"update,"
"visit,"
"visualize,"
////////////////
"allow,"
"reserve,"
"pull,"
"exclude,"
"destroy,"
"consider,"
"advance,"
"examine,"
"decline,"
"express,"
"establish,"
"sit,"
"exist,"
"arise,"
"lose,"
"desire,"
"associate,"
"contact,"
"identify,"
"register,"
"join,"
"demand,"
"plan,"
"postpone,"
"abandon,"
"listen,"
"direct,"
"preserve,"
"belong,"
"conclude,"
;


	//AddKeyword(sKeywords, CLR_KEYWORD, GRP_KEYWORD);
	//AddKeyword(sDirectives, CLR_KEYWORD, GRP_KEYWORD);
	//AddKeyword(sPragmas, CLR_KEYWORD, GRP_KEYWORD);

   AddKeyword(sKeywords, RGB(255, 128, 0), GRP_KEYWORD);
   AddKeyword(sDirectives, RGB(255, 0, 0), GRP_KEYWORD);
   AddKeyword(sVerbsContext, RGB(0, 0, 255), GRP_KEYWORD);
   AddKeyword(sVerbsExtended, RGB(0, 0, 255), GRP_KEYWORD);
   AddKeyword("REM,Rem,rem", RGB(255, 0, 255), 4);
}

void CSyntaxColorizer::createTables()
{
	m_pTableZero = new unsigned char[256];
   m_pTableOne   = new unsigned char[256];
	m_pTableTwo  = new unsigned char[256];
   m_pTableThree = new unsigned char[256];
	m_pTableFour = new unsigned char[256];
   m_pAllowable  = new unsigned char[256];

	memset(m_pTableZero, SKIP, 256);
   memset(m_pTableOne, SKIP, 256);
	memset(m_pTableTwo, SKIP, 256);
   memset(m_pTableThree, SKIP, 256);
	memset(m_pTableFour, SKIP, 256);
   memset(m_pAllowable, false, 256);

	*(m_pTableZero + '"') = DQSTART; *(m_pTableZero + '\'')  = SQSTART;
	*(m_pTableZero + '/') = CMSTART; *(m_pTableOne + '"')    = DQEND;
	*(m_pTableTwo + '\'') = SQEND;   *(m_pTableThree + '\n') = SLEND;
	*(m_pTableFour + '*') = MLEND;

	*(m_pAllowable + '\n') = true; *(m_pAllowable + '\r') = true;
	*(m_pAllowable + '\t') = true; *(m_pAllowable + '\0') = true;
	*(m_pAllowable + ' ')  = true; *(m_pAllowable + ';')  = true;
	*(m_pAllowable + '(')  = true; *(m_pAllowable + ')')  = true;
	*(m_pAllowable + '{')  = true; *(m_pAllowable + '}')  = true;
	*(m_pAllowable + '[')  = true; *(m_pAllowable + ']')  = true;
	*(m_pAllowable + '*')  = true;
	*(m_pAllowable + ',')  = true;
	*(m_pAllowable + '.')  = true;
	*(m_pAllowable + '!')  = true;
	*(m_pAllowable + '?')  = true;
   *(m_pAllowable + ':')  = true;
   *(m_pAllowable + '/')  = true;
}

void CSyntaxColorizer::deleteTables()
{
	delete m_pTableZero;
   delete m_pTableOne;
   delete m_pTableTwo;
	delete m_pTableThree;
   delete m_pTableFour;
   delete m_pAllowable;
}

void CSyntaxColorizer::AddKeyword(LPCTSTR Keyword, COLORREF cr, int grp)
{
	LPTSTR token;

	//make a copy of Keyword so that strtok will operate correctly
	LPTSTR keyword = new TCHAR[strlen(Keyword) + 1];
	strcpy(keyword, Keyword);

	CHARFORMAT cf = m_cfDefault;
	cf.crTextColor = cr;

	token = strtok(keyword,",");
	while(token != NULL)
	{
		if(_stricmp(token, "rem") == 0)
			*(m_pTableTwo + '\n') = SLEND; //set single quote as comment start
		addKey(token, cf, grp);
		token = strtok(NULL, ",");
	}
	delete keyword;
}

void CSyntaxColorizer::AddKeyword(LPCTSTR Keyword, CHARFORMAT cf, int grp)
{
	LPTSTR token;

	//make a copy of Keyword so that strtok will operate correctly
	LPTSTR keyword = new TCHAR[strlen(Keyword) + 1];
	strcpy(keyword,Keyword);

	token = strtok(keyword,",");
	while(token != NULL)
	{
		if(_stricmp(token,"rem") == 0)
			*(m_pTableTwo + '\n') = SLEND; //set single quote as comment start
		addKey(token,cf,grp);
		token = strtok(NULL,",");
	}
	delete keyword;
}

void CSyntaxColorizer::addKey(LPCTSTR Keyword, CHARFORMAT cf, int grp) //add in ascending order
{
	SKeyword* pskNewKey = new SKeyword;
	SKeyword* prev, *curr;

	//the string pointed to by Keyword is only temporary, so make a copy 
	// of it for our list
	pskNewKey->keyword = new TCHAR[strlen(Keyword)+1];
	strcpy(pskNewKey->keyword, Keyword);

	pskNewKey->keylen = strlen(Keyword);
	pskNewKey->cf = cf;
	pskNewKey->group = grp;
	pskNewKey->pNext = NULL;
	*(m_pTableZero + pskNewKey->keyword[0]) = KEYWORD;

	//if list is empty, add first node
	if(m_pskKeyword == NULL)
		m_pskKeyword = pskNewKey; 
	else
	{
		//check to see if new node goes before first node
		if(strcmp(Keyword, m_pskKeyword->keyword) < 0)
		{
			pskNewKey->pNext = m_pskKeyword;
			m_pskKeyword = pskNewKey;
		}
		//check to see if new keyword already exists at the first node
		else if(strcmp(Keyword,m_pskKeyword->keyword) == 0)
		{
			//the keyword exists, so replace the existing with the new
			pskNewKey->pNext = m_pskKeyword->pNext;
			delete m_pskKeyword->keyword;
         delete m_pskKeyword;
			m_pskKeyword = pskNewKey;
		}
		else
		{
			prev = m_pskKeyword;
			curr = m_pskKeyword->pNext;
			while(curr != NULL && strcmp(curr->keyword,Keyword) < 0)
			{
				prev = curr;
				curr = curr->pNext;
			}
			if(curr != NULL && strcmp(curr->keyword,Keyword) == 0)
			{
				//the keyword exists, so replace the existing with the new
				prev->pNext = pskNewKey;
				pskNewKey->pNext = curr->pNext;
				delete curr->keyword; delete curr;
			}
			else
			{
				pskNewKey->pNext = curr;
				prev->pNext = pskNewKey;
			}
		}
	}
}

void CSyntaxColorizer::ClearKeywordList()
{
	SKeyword* pTemp = m_pskKeyword;

	while(m_pskKeyword != NULL)
	{
		*(m_pTableZero + m_pskKeyword->keyword[0]) = SKIP;
		if(_stricmp(m_pskKeyword->keyword,"rem") == 0)
			*(m_pTableTwo + '\n') = SKIP;
		pTemp = m_pskKeyword->pNext;
		delete m_pskKeyword->keyword;
		delete m_pskKeyword;
		m_pskKeyword = pTemp;
	}
}

CString CSyntaxColorizer::GetKeywordList()
{
	CString sList;
	SKeyword* pTemp = m_pskKeyword;

	while(pTemp != NULL)
	{
		sList += pTemp->keyword;
		sList += ",";
		pTemp = pTemp->pNext;
	}
	sList.TrimRight(',');
	return sList;
}

CString CSyntaxColorizer::GetKeywordList(int grp)
{
	CString sList;
	SKeyword* pTemp = m_pskKeyword;

	while(pTemp != NULL)
	{
		if(pTemp->group == grp)
		{
			sList += pTemp->keyword;
			sList += ",";
		}
		pTemp = pTemp->pNext;
	}
	sList.TrimRight(',');
	return sList;
}

void CSyntaxColorizer::SetCommentColor(COLORREF cr)
{
	CHARFORMAT cf = m_cfComment;

	cf.dwMask = CFM_COLOR;
	cf.crTextColor = cr;

	SetCommentStyle(cf);
}

void CSyntaxColorizer::SetStringColor(COLORREF cr)
{
	CHARFORMAT cf = m_cfString;

	cf.dwMask = CFM_COLOR;
	cf.crTextColor = cr;

	SetStringStyle(cf);
}

void CSyntaxColorizer::SetGroupStyle(int grp, CHARFORMAT cf)
{
	SKeyword* pTemp = m_pskKeyword;

	while(pTemp != NULL)
	{
		if(pTemp->group == grp)
		{
			pTemp->cf = cf;
		}
		pTemp = pTemp->pNext;
	}
}

void CSyntaxColorizer::GetGroupStyle(int grp, CHARFORMAT &cf)
{
	SKeyword* pTemp = m_pskKeyword;

	while(pTemp != NULL)
	{
		if(pTemp->group == grp)
		{
			cf = pTemp->cf;
			pTemp = NULL;
		}
		else
		{
			pTemp = pTemp->pNext;
			//if grp is not found, return default style
			if(pTemp == NULL) cf = m_cfDefault;
		}
	}
}

void CSyntaxColorizer::SetGroupColor(int grp, COLORREF cr)
{
	CHARFORMAT cf;
	GetGroupStyle(grp,cf);

	cf.dwMask = CFM_COLOR;
	cf.crTextColor = cr;

	SetGroupStyle(grp,cf);
}

void CSyntaxColorizer::Colorize(CHARRANGE cr, CRichEditCtrl *pCtrl)
{
	long nTextLength = 0;

	if(cr.cpMin == 0 && cr.cpMax == -1) //send entire text of rich edit box
	{
		//set up the buffer to hold the text from the rich edit box
		nTextLength = pCtrl->GetTextLength();

		//if there is alot of text in the Rich Edit (>64K) then GetWindowText doesn't
		//work. We have to select all of the text, and then use GetSelText
		pCtrl->SetSel(0,-1);

	}
	else
	{
		//set up the buffer to hold the text
		nTextLength = cr.cpMax - cr.cpMin + 1;//add 1 because zero-based array

		//get the text
		pCtrl->SetSel(cr.cpMin,cr.cpMax);
	}
	
	LPTSTR lpszBuf = new TCHAR[nTextLength+1];
	pCtrl->GetSelText(lpszBuf);
	pCtrl->SetSelectionCharFormat(m_cfDefault);

	colorize(lpszBuf,pCtrl,cr.cpMin);

	delete lpszBuf;
}

void CSyntaxColorizer::Colorize(long nStartChar, long nEndChar, CRichEditCtrl *pCtrl)
{
	long nTextLength = 0;

	if(nStartChar == 0 && nEndChar == -1) //send entire text of rich edit box
	{
		nTextLength = pCtrl->GetTextLength();

		//if there is alot of text in the Rich Edit (>64K) then GetWindowText doesn't
		//work. We have to select all of the text, and then use GetSelText
		pCtrl->SetSel(0,-1);
	}
	else
	{
		//set up the text buffer; add 1 because zero-based array
		nTextLength = nEndChar - nStartChar + 1;

		pCtrl->SetSel(nStartChar,nEndChar);
	}
	
	LPTSTR lpszBuf = new TCHAR[nTextLength+1];
	pCtrl->GetSelText(lpszBuf);
	pCtrl->SetSelectionCharFormat(m_cfDefault);

	colorize(lpszBuf, pCtrl, nStartChar);

	delete lpszBuf;
}

void CSyntaxColorizer::colorize(LPTSTR lpszBuf, CRichEditCtrl *pCtrl, long iOffset /*=0*/)
{
	//setup some vars
	CHARFORMAT cf;
	LPTSTR lpszTemp;
	long iStart;
	long x = 0;
	SKeyword* pskTemp = m_pskKeyword;
	unsigned char* pTable = m_pTableZero;

	//do the work
	while(lpszBuf[x])
	{
		lpszTemp = lpszBuf + x;
		while(pskTemp != NULL)
		{
			if (pskTemp->keyword[0] == char(tolower(lpszTemp[0])))
			{
				int x1 = 0, y1 = 0;
            iStart = iOffset + x;
				while (pskTemp->keyword[x1])
				{
					y1 += char(tolower(lpszTemp[x1])) ^ pskTemp->keyword[x1];
					x1++;
				}
				if (y1 == 0 && (*(m_pAllowable + char(tolower(lpszBuf[x-1]))) && 
						*(m_pAllowable + char(tolower(lpszBuf[x + pskTemp->keylen])))
                  ))
				{
					if(_stricmp(pskTemp->keyword, "rem") == 0)
					{
						pTable = m_pTableThree;
					}
					else 
					{
						x += pskTemp->keylen;
						pCtrl->SetSel(iStart, iOffset + x);
						pCtrl->SetSelectionCharFormat(pskTemp->cf);
					}
				}
			}
			pskTemp = pskTemp->pNext;
		}
		pskTemp = m_pskKeyword;

		x++;
	}
	//sometimes we get to the end of the file before the end of the string
	//or comment, so we deal with that situation here
	if(pTable == m_pTableOne)
	{
		cf = m_cfString;
		pCtrl->SetSel(iStart,iOffset + x+1);
		pCtrl->SetSelectionCharFormat(cf);
	}
	else if(pTable == m_pTableTwo)
	{
		cf = m_cfString;
		pCtrl->SetSel(iStart,iOffset + x+1);
		pCtrl->SetSelectionCharFormat(cf);
	}
	else if(pTable == m_pTableThree)
	{
		cf = m_cfComment;
		pCtrl->SetSel(iStart,iOffset + x+1);
		pCtrl->SetSelectionCharFormat(cf);
	}
	else if(pTable == m_pTableFour)
	{
		cf = m_cfComment;
		pCtrl->SetSel(iStart,iOffset + x+1);
		pCtrl->SetSelectionCharFormat(cf);
	}
}



