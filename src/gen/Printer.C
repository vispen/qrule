/*** BNFC-Generated Pretty Printer and Abstract Syntax Viewer ***/

#include <string>
#include "Printer.H"
#define INDENT_WIDTH 2


//You may wish to change render
void PrintAbsyn::render(Char c)
{
  if (c == '{')
  {
     bufAppend('\n');
     indent();
     bufAppend(c);
     _n_ = _n_ + INDENT_WIDTH;
     bufAppend('\n');
     indent();
  }
  else if (c == '(' || c == '[')
     bufAppend(c);
  else if (c == ')' || c == ']')
  {
     backup();
     bufAppend(c);
  }
  else if (c == '}')
  {
     int t;
     _n_ = _n_ - INDENT_WIDTH;
     for (t=0; t<INDENT_WIDTH; t++) {
       backup();
     }
     bufAppend(c);
     bufAppend('\n');
     indent();
  }
  else if (c == ',')
  {
     backup();
     bufAppend(c);
     bufAppend(' ');
  }
  else if (c == ';')
  {
     backup();
     bufAppend(c);
     bufAppend('\n');
     indent();
  }
  else if (c == 0) return;
  else
  {
     bufAppend(' ');
     bufAppend(c);
     bufAppend(' ');
  }
}
void PrintAbsyn::render(String s_)
{
  const char *s = s_.c_str() ;
  if(strlen(s) > 0)
  {
    bufAppend(s);
    bufAppend(' ');
  }
}
void PrintAbsyn::render(char* s)
{
  if(strlen(s) > 0)
  {
    bufAppend(s);
    bufAppend(' ');
  }
}
void PrintAbsyn::indent()
{
  int n = _n_;
  while (n > 0)
  {
    bufAppend(' ');
    n--;
  }
}
void PrintAbsyn::backup()
{
  if (buf_[cur_ - 1] == ' ')
  {
    buf_[cur_ - 1] = 0;
    cur_--;
  }
}
PrintAbsyn::PrintAbsyn(void)
{
  _i_ = 0; _n_ = 0;
  buf_ = 0;
  bufReset();
}

PrintAbsyn::~PrintAbsyn(void)
{
}

char* PrintAbsyn::print(Visitable *v)
{
  _i_ = 0; _n_ = 0;
  bufReset();
  v->accept(this);
  return buf_;
}
RetType* PrintAbsyn::visitRuleSet(RuleSet*p) {} //abstract class

RetType* PrintAbsyn::visitRSet(RSet* p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  if(p->listrule_) {_i_ = 0; p->listrule_->accept(this);}
  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

RetType* PrintAbsyn::visitRule(Rule*p) {} //abstract class

RetType* PrintAbsyn::visitRRule(RRule* p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  _i_ = 0; p->tag_->accept(this);
  _i_ = 0; p->severity_->accept(this);
  _i_ = 0; p->rulecause_->accept(this);
  _i_ = 0; p->astscope_->accept(this);
  _i_ = 0; p->explanation_->accept(this);
  render("::");
  _i_ = 0; p->expr_->accept(this);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

RetType* PrintAbsyn::visitASTScope(ASTScope*p) {} //abstract class

RetType* PrintAbsyn::visitASTGlobally(ASTGlobally* p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render("Globally");

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

RetType* PrintAbsyn::visitASTFile(ASTFile* p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render("File");

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

RetType* PrintAbsyn::visitASTImported(ASTImported* p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render("Imported");

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

RetType* PrintAbsyn::visitRuleCause(RuleCause*p) {} //abstract class

RetType* PrintAbsyn::visitRCLang(RCLang* p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render("Language");

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

RetType* PrintAbsyn::visitRCPolicy(RCPolicy* p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render("Policy");

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

RetType* PrintAbsyn::visitExplanation(Explanation*p) {} //abstract class

RetType* PrintAbsyn::visitExplan(Explan* p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render("??");
  visitString(p->string_);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

RetType* PrintAbsyn::visitNoexplan(Noexplan* p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render("");

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

RetType* PrintAbsyn::visitListRule(ListRule *listrule)
{
  for (ListRule::const_iterator i = listrule->begin() ; i != listrule->end() ; ++i)
  {
    (*i)->accept(this);
    if (i != listrule->end() - 1) render(',');
  }
}RetType* PrintAbsyn::visitTag(Tag*p) {} //abstract class

RetType* PrintAbsyn::visitTTag(TTag* p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  visitString(p->string_);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

RetType* PrintAbsyn::visitSeverity(Severity*p) {} //abstract class

RetType* PrintAbsyn::visitSevWarning(SevWarning* p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render("Warning");

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

RetType* PrintAbsyn::visitSevCritical(SevCritical* p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render("Critical");

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

RetType* PrintAbsyn::visitOverPaths(OverPaths*p) {} //abstract class

RetType* PrintAbsyn::visitAll(All* p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render('A');
  _i_ = 0; p->pathspecific_->accept(this);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

RetType* PrintAbsyn::visitExist(Exist* p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render('E');
  _i_ = 0; p->pathspecific_->accept(this);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

RetType* PrintAbsyn::visitPathSpecific(PathSpecific*p) {} //abstract class

RetType* PrintAbsyn::visitFuture(Future* p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render('F');
  _i_ = 0; p->expr_->accept(this);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

RetType* PrintAbsyn::visitGlobally(Globally* p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render('G');
  _i_ = 0; p->expr_->accept(this);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

RetType* PrintAbsyn::visitUntil(Until* p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  _i_ = 0; p->expr_1->accept(this);
  render('U');
  _i_ = 0; p->expr_2->accept(this);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

RetType* PrintAbsyn::visitNext(Next* p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render('X');
  _i_ = 0; p->expr_->accept(this);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

RetType* PrintAbsyn::visitIStmnt(IStmnt*p) {} //abstract class

RetType* PrintAbsyn::visitIEInt(IEInt* p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  visitInteger(p->integer_);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

RetType* PrintAbsyn::visitIENrChildren(IENrChildren* p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render("nrChildren");

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

RetType* PrintAbsyn::visitIExpr(IExpr*p) {} //abstract class

RetType* PrintAbsyn::visitIELtEq(IELtEq* p)
{
  int oldi = _i_;
  if (oldi > 2) render(_L_PAREN);

  _i_ = 1; p->iexpr_->accept(this);
  render("<=");
  _i_ = 0; p->istmnt_->accept(this);

  if (oldi > 2) render(_R_PAREN);

  _i_ = oldi;
}

RetType* PrintAbsyn::visitIEGtEq(IEGtEq* p)
{
  int oldi = _i_;
  if (oldi > 2) render(_L_PAREN);

  _i_ = 1; p->iexpr_->accept(this);
  render(">=");
  _i_ = 0; p->istmnt_->accept(this);

  if (oldi > 2) render(_R_PAREN);

  _i_ = oldi;
}

RetType* PrintAbsyn::visitIELt(IELt* p)
{
  int oldi = _i_;
  if (oldi > 2) render(_L_PAREN);

  _i_ = 1; p->iexpr_->accept(this);
  render('<');
  _i_ = 0; p->istmnt_->accept(this);

  if (oldi > 2) render(_R_PAREN);

  _i_ = oldi;
}

RetType* PrintAbsyn::visitIEGt(IEGt* p)
{
  int oldi = _i_;
  if (oldi > 2) render(_L_PAREN);

  _i_ = 1; p->iexpr_->accept(this);
  render('>');
  _i_ = 0; p->istmnt_->accept(this);

  if (oldi > 2) render(_R_PAREN);

  _i_ = oldi;
}

RetType* PrintAbsyn::visitIEq(IEq* p)
{
  int oldi = _i_;
  if (oldi > 2) render(_L_PAREN);

  _i_ = 0; p->istmnt_1->accept(this);
  render('=');
  _i_ = 0; p->istmnt_2->accept(this);

  if (oldi > 2) render(_R_PAREN);

  _i_ = oldi;
}

RetType* PrintAbsyn::visitIEStmnt(IEStmnt* p)
{
  int oldi = _i_;
  if (oldi > 1) render(_L_PAREN);

  _i_ = 0; p->istmnt_->accept(this);

  if (oldi > 1) render(_R_PAREN);

  _i_ = oldi;
}

RetType* PrintAbsyn::visitExpr(Expr*p) {} //abstract class

RetType* PrintAbsyn::visitETrue(ETrue* p)
{
  int oldi = _i_;
  if (oldi > 10) render(_L_PAREN);

  render("True");

  if (oldi > 10) render(_R_PAREN);

  _i_ = oldi;
}

RetType* PrintAbsyn::visitEFalse(EFalse* p)
{
  int oldi = _i_;
  if (oldi > 10) render(_L_PAREN);

  render("False");

  if (oldi > 10) render(_R_PAREN);

  _i_ = oldi;
}

RetType* PrintAbsyn::visitENodeVal(ENodeVal* p)
{
  int oldi = _i_;
  if (oldi > 10) render(_L_PAREN);

  render("value");
  visitString(p->string_);

  if (oldi > 10) render(_R_PAREN);

  _i_ = oldi;
}

RetType* PrintAbsyn::visitEType(EType* p)
{
  int oldi = _i_;
  if (oldi > 10) render(_L_PAREN);

  render("type");
  _i_ = 0; p->type_->accept(this);

  if (oldi > 10) render(_R_PAREN);

  _i_ = oldi;
}

RetType* PrintAbsyn::visitEParant(EParant* p)
{
  int oldi = _i_;
  if (oldi > 10) render(_L_PAREN);

  render('(');
  _i_ = 1; p->expr_->accept(this);
  render(')');

  if (oldi > 10) render(_R_PAREN);

  _i_ = oldi;
}

RetType* PrintAbsyn::visitENot(ENot* p)
{
  int oldi = _i_;
  if (oldi > 9) render(_L_PAREN);

  render('!');
  _i_ = 10; p->expr_->accept(this);

  if (oldi > 9) render(_R_PAREN);

  _i_ = oldi;
}

RetType* PrintAbsyn::visitEImpl(EImpl* p)
{
  int oldi = _i_;
  if (oldi > 8) render(_L_PAREN);

  _i_ = 8; p->expr_1->accept(this);
  render("->");
  _i_ = 9; p->expr_2->accept(this);

  if (oldi > 8) render(_R_PAREN);

  _i_ = oldi;
}

RetType* PrintAbsyn::visitEIExpr(EIExpr* p)
{
  int oldi = _i_;
  if (oldi > 7) render(_L_PAREN);

  _i_ = 2; p->iexpr_->accept(this);

  if (oldi > 7) render(_R_PAREN);

  _i_ = oldi;
}

RetType* PrintAbsyn::visitEEq(EEq* p)
{
  int oldi = _i_;
  if (oldi > 6) render(_L_PAREN);

  _i_ = 6; p->expr_1->accept(this);
  render('=');
  _i_ = 7; p->expr_2->accept(this);

  if (oldi > 6) render(_R_PAREN);

  _i_ = oldi;
}

RetType* PrintAbsyn::visitEAnd(EAnd* p)
{
  int oldi = _i_;
  if (oldi > 4) render(_L_PAREN);

  _i_ = 4; p->expr_1->accept(this);
  render('&');
  _i_ = 5; p->expr_2->accept(this);

  if (oldi > 4) render(_R_PAREN);

  _i_ = oldi;
}

RetType* PrintAbsyn::visitEOr(EOr* p)
{
  int oldi = _i_;
  if (oldi > 4) render(_L_PAREN);

  _i_ = 4; p->expr_1->accept(this);
  render('|');
  _i_ = 5; p->expr_2->accept(this);

  if (oldi > 4) render(_R_PAREN);

  _i_ = oldi;
}

RetType* PrintAbsyn::visitEOverPaths(EOverPaths* p)
{
  int oldi = _i_;
  if (oldi > 2) render(_L_PAREN);

  _i_ = 0; p->overpaths_->accept(this);

  if (oldi > 2) render(_R_PAREN);

  _i_ = oldi;
}

RetType* PrintAbsyn::visitListExpr(ListExpr *listexpr)
{
  for (ListExpr::const_iterator i = listexpr->begin() ; i != listexpr->end() ; ++i)
  {
    (*i)->accept(this);
    render("");
  }
}RetType* PrintAbsyn::visitType(Type*p) {} //abstract class

RetType* PrintAbsyn::visitTType(TType* p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  visitString(p->string_);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

RetType* PrintAbsyn::visitParam(Param*p) {} //abstract class

RetType* PrintAbsyn::visitPParam(PParam* p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  visitString(p->string_);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

RetType* PrintAbsyn::visitInteger(Integer i)
{
  char tmp[16];
  sprintf(tmp, "%d", i);
  bufAppend(tmp);
}
RetType* PrintAbsyn::visitDouble(Double d)
{
  char tmp[16];
  sprintf(tmp, "%g", d);
  bufAppend(tmp);
}
RetType* PrintAbsyn::visitChar(Char c)
{
  bufAppend('\'');
  bufAppend(c);
  bufAppend('\'');
}
RetType* PrintAbsyn::visitString(String s)
{
  bufAppend('\"');
  bufAppend(s);
  bufAppend('\"');
}
RetType* PrintAbsyn::visitIdent(String s)
{
  render(s);
}

ShowAbsyn::ShowAbsyn(void)
{
  buf_ = 0;
  bufReset();
}

ShowAbsyn::~ShowAbsyn(void)
{
}

char* ShowAbsyn::show(Visitable *v)
{
  bufReset();
  v->accept(this);
  return buf_;
}
RetType* ShowAbsyn::visitRuleSet(RuleSet* p) {} //abstract class

RetType* ShowAbsyn::visitRSet(RSet* p)
{
  bufAppend('(');
  bufAppend("RSet");
  bufAppend(' ');
  bufAppend('[');
  if (p->listrule_)  p->listrule_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
RetType* ShowAbsyn::visitRule(Rule* p) {} //abstract class

RetType* ShowAbsyn::visitRRule(RRule* p)
{
  bufAppend('(');
  bufAppend("RRule");
  bufAppend(' ');
  bufAppend('[');
  if (p->tag_)  p->tag_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend('[');
  if (p->severity_)  p->severity_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend('[');
  if (p->rulecause_)  p->rulecause_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend('[');
  if (p->astscope_)  p->astscope_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend('[');
  if (p->explanation_)  p->explanation_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend('[');
  if (p->expr_)  p->expr_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
RetType* ShowAbsyn::visitASTScope(ASTScope* p) {} //abstract class

RetType* ShowAbsyn::visitASTGlobally(ASTGlobally* p)
{
  bufAppend("ASTGlobally");
}
RetType* ShowAbsyn::visitASTFile(ASTFile* p)
{
  bufAppend("ASTFile");
}
RetType* ShowAbsyn::visitASTImported(ASTImported* p)
{
  bufAppend("ASTImported");
}
RetType* ShowAbsyn::visitRuleCause(RuleCause* p) {} //abstract class

RetType* ShowAbsyn::visitRCLang(RCLang* p)
{
  bufAppend("RCLang");
}
RetType* ShowAbsyn::visitRCPolicy(RCPolicy* p)
{
  bufAppend("RCPolicy");
}
RetType* ShowAbsyn::visitExplanation(Explanation* p) {} //abstract class

RetType* ShowAbsyn::visitExplan(Explan* p)
{
  bufAppend('(');
  bufAppend("Explan");
  bufAppend(' ');
  visitString(p->string_);
  bufAppend(')');
}
RetType* ShowAbsyn::visitNoexplan(Noexplan* p)
{
  bufAppend("Noexplan");
}
RetType* ShowAbsyn::visitListRule(ListRule *listrule)
{
  for (ListRule::const_iterator i = listrule->begin() ; i != listrule->end() ; ++i)
  {
    (*i)->accept(this);
    if (i != listrule->end() - 1) bufAppend(", ");
  }
}

RetType* ShowAbsyn::visitTag(Tag* p) {} //abstract class

RetType* ShowAbsyn::visitTTag(TTag* p)
{
  bufAppend('(');
  bufAppend("TTag");
  bufAppend(' ');
  visitString(p->string_);
  bufAppend(')');
}
RetType* ShowAbsyn::visitSeverity(Severity* p) {} //abstract class

RetType* ShowAbsyn::visitSevWarning(SevWarning* p)
{
  bufAppend("SevWarning");
}
RetType* ShowAbsyn::visitSevCritical(SevCritical* p)
{
  bufAppend("SevCritical");
}
RetType* ShowAbsyn::visitOverPaths(OverPaths* p) {} //abstract class

RetType* ShowAbsyn::visitAll(All* p)
{
  bufAppend('(');
  bufAppend("All");
  bufAppend(' ');
  bufAppend('[');
  if (p->pathspecific_)  p->pathspecific_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
RetType* ShowAbsyn::visitExist(Exist* p)
{
  bufAppend('(');
  bufAppend("Exist");
  bufAppend(' ');
  bufAppend('[');
  if (p->pathspecific_)  p->pathspecific_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
RetType* ShowAbsyn::visitPathSpecific(PathSpecific* p) {} //abstract class

RetType* ShowAbsyn::visitFuture(Future* p)
{
  bufAppend('(');
  bufAppend("Future");
  bufAppend(' ');
  bufAppend('[');
  if (p->expr_)  p->expr_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
RetType* ShowAbsyn::visitGlobally(Globally* p)
{
  bufAppend('(');
  bufAppend("Globally");
  bufAppend(' ');
  bufAppend('[');
  if (p->expr_)  p->expr_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
RetType* ShowAbsyn::visitUntil(Until* p)
{
  bufAppend('(');
  bufAppend("Until");
  bufAppend(' ');
  p->expr_1->accept(this);
  bufAppend(' ');
  p->expr_2->accept(this);
  bufAppend(')');
}
RetType* ShowAbsyn::visitNext(Next* p)
{
  bufAppend('(');
  bufAppend("Next");
  bufAppend(' ');
  bufAppend('[');
  if (p->expr_)  p->expr_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
RetType* ShowAbsyn::visitIStmnt(IStmnt* p) {} //abstract class

RetType* ShowAbsyn::visitIEInt(IEInt* p)
{
  bufAppend('(');
  bufAppend("IEInt");
  bufAppend(' ');
  visitInteger(p->integer_);
  bufAppend(')');
}
RetType* ShowAbsyn::visitIENrChildren(IENrChildren* p)
{
  bufAppend("IENrChildren");
}
RetType* ShowAbsyn::visitIExpr(IExpr* p) {} //abstract class

RetType* ShowAbsyn::visitIELtEq(IELtEq* p)
{
  bufAppend('(');
  bufAppend("IELtEq");
  bufAppend(' ');
  bufAppend('[');
  if (p->iexpr_)  p->iexpr_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend('[');
  if (p->istmnt_)  p->istmnt_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
RetType* ShowAbsyn::visitIEGtEq(IEGtEq* p)
{
  bufAppend('(');
  bufAppend("IEGtEq");
  bufAppend(' ');
  bufAppend('[');
  if (p->iexpr_)  p->iexpr_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend('[');
  if (p->istmnt_)  p->istmnt_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
RetType* ShowAbsyn::visitIELt(IELt* p)
{
  bufAppend('(');
  bufAppend("IELt");
  bufAppend(' ');
  bufAppend('[');
  if (p->iexpr_)  p->iexpr_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend('[');
  if (p->istmnt_)  p->istmnt_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
RetType* ShowAbsyn::visitIEGt(IEGt* p)
{
  bufAppend('(');
  bufAppend("IEGt");
  bufAppend(' ');
  bufAppend('[');
  if (p->iexpr_)  p->iexpr_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend('[');
  if (p->istmnt_)  p->istmnt_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
RetType* ShowAbsyn::visitIEq(IEq* p)
{
  bufAppend('(');
  bufAppend("IEq");
  bufAppend(' ');
  p->istmnt_1->accept(this);
  bufAppend(' ');
  p->istmnt_2->accept(this);
  bufAppend(')');
}
RetType* ShowAbsyn::visitIEStmnt(IEStmnt* p)
{
  bufAppend('(');
  bufAppend("IEStmnt");
  bufAppend(' ');
  bufAppend('[');
  if (p->istmnt_)  p->istmnt_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
RetType* ShowAbsyn::visitExpr(Expr* p) {} //abstract class

RetType* ShowAbsyn::visitETrue(ETrue* p)
{
  bufAppend("ETrue");
}
RetType* ShowAbsyn::visitEFalse(EFalse* p)
{
  bufAppend("EFalse");
}
RetType* ShowAbsyn::visitENodeVal(ENodeVal* p)
{
  bufAppend('(');
  bufAppend("ENodeVal");
  bufAppend(' ');
  visitString(p->string_);
  bufAppend(')');
}
RetType* ShowAbsyn::visitEType(EType* p)
{
  bufAppend('(');
  bufAppend("EType");
  bufAppend(' ');
  bufAppend('[');
  if (p->type_)  p->type_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
RetType* ShowAbsyn::visitEParant(EParant* p)
{
  bufAppend('(');
  bufAppend("EParant");
  bufAppend(' ');
  bufAppend('[');
  if (p->expr_)  p->expr_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend(')');
}
RetType* ShowAbsyn::visitENot(ENot* p)
{
  bufAppend('(');
  bufAppend("ENot");
  bufAppend(' ');
  bufAppend('[');
  if (p->expr_)  p->expr_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
RetType* ShowAbsyn::visitEImpl(EImpl* p)
{
  bufAppend('(');
  bufAppend("EImpl");
  bufAppend(' ');
  p->expr_1->accept(this);
  bufAppend(' ');
  p->expr_2->accept(this);
  bufAppend(')');
}
RetType* ShowAbsyn::visitEIExpr(EIExpr* p)
{
  bufAppend('(');
  bufAppend("EIExpr");
  bufAppend(' ');
  bufAppend('[');
  if (p->iexpr_)  p->iexpr_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
RetType* ShowAbsyn::visitEEq(EEq* p)
{
  bufAppend('(');
  bufAppend("EEq");
  bufAppend(' ');
  p->expr_1->accept(this);
  bufAppend(' ');
  p->expr_2->accept(this);
  bufAppend(')');
}
RetType* ShowAbsyn::visitEAnd(EAnd* p)
{
  bufAppend('(');
  bufAppend("EAnd");
  bufAppend(' ');
  p->expr_1->accept(this);
  bufAppend(' ');
  p->expr_2->accept(this);
  bufAppend(')');
}
RetType* ShowAbsyn::visitEOr(EOr* p)
{
  bufAppend('(');
  bufAppend("EOr");
  bufAppend(' ');
  p->expr_1->accept(this);
  bufAppend(' ');
  p->expr_2->accept(this);
  bufAppend(')');
}
RetType* ShowAbsyn::visitEOverPaths(EOverPaths* p)
{
  bufAppend('(');
  bufAppend("EOverPaths");
  bufAppend(' ');
  bufAppend('[');
  if (p->overpaths_)  p->overpaths_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
RetType* ShowAbsyn::visitListExpr(ListExpr *listexpr)
{
  for (ListExpr::const_iterator i = listexpr->begin() ; i != listexpr->end() ; ++i)
  {
    (*i)->accept(this);
    if (i != listexpr->end() - 1) bufAppend(", ");
  }
}

RetType* ShowAbsyn::visitType(Type* p) {} //abstract class

RetType* ShowAbsyn::visitTType(TType* p)
{
  bufAppend('(');
  bufAppend("TType");
  bufAppend(' ');
  visitString(p->string_);
  bufAppend(')');
}
RetType* ShowAbsyn::visitParam(Param* p) {} //abstract class

RetType* ShowAbsyn::visitPParam(PParam* p)
{
  bufAppend('(');
  bufAppend("PParam");
  bufAppend(' ');
  visitString(p->string_);
  bufAppend(')');
}
RetType* ShowAbsyn::visitInteger(Integer i)
{
  char tmp[16];
  sprintf(tmp, "%d", i);
  bufAppend(tmp);
}
RetType* ShowAbsyn::visitDouble(Double d)
{
  char tmp[16];
  sprintf(tmp, "%g", d);
  bufAppend(tmp);
}
RetType* ShowAbsyn::visitChar(Char c)
{
  bufAppend('\'');
  bufAppend(c);
  bufAppend('\'');
}
RetType* ShowAbsyn::visitString(String s)
{
  bufAppend('\"');
  bufAppend(s);
  bufAppend('\"');
}
RetType* ShowAbsyn::visitIdent(String s)
{
  bufAppend('\"');
  bufAppend(s);
  bufAppend('\"');
}

