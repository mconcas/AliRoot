#ifndef ALIEXPRESSION_H
#define ALIEXPRESSION_H

/* Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
 * See cxx source for full Copyright notice                               */

/* $Id$ */

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//  AliExpression Class                                                      //                                                                           //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#include <TObject.h>
class TString;
class TObjArray;

// These are the valid operators types.

enum { kOpAND,     // AND '&'
       kOpOR,      // OR '|'
       kOpNOT };   // Unary negation '!'

class AliExpression : public TObject {

public:
                           AliExpression() : fArg1(0), fArg2(0), fOperator(0) {}
                           AliExpression( TString exp );
               virtual    ~AliExpression();
                           AliExpression( const AliExpression& exp ) : TObject( exp ),
                                          fArg1(exp.fArg1), fArg2(exp.fArg2), fOperator(exp.fOperator) {}
         AliExpression&    operator=(const AliExpression& exp);

        virtual Bool_t     Value( TObjArray & vars );
       virtual TString     Unparse() const;

private:
         AliExpression*    fArg1;         // left argument
         AliExpression*    fArg2;         // right argument
                 Int_t     fOperator;     // operator

                           AliExpression( int op, AliExpression* a );
                           AliExpression( int op, AliExpression* a, AliExpression* b );

             TObjArray*    Tokenize( TString str ) const;
  static AliExpression*    Element( TObjArray &st, Int_t &i );
  static AliExpression*    Primary( TObjArray &st, Int_t &i );
  static AliExpression*    Expression( TObjArray &st, Int_t &i );

   ClassDef( AliExpression, 1 )  // Class to evaluate an expression
};




///////////////////////////////////////////////////////////////////////////

class AliVariableExpression: public AliExpression {
public:
                     AliVariableExpression( TString a ): AliExpression(), fVname(a) {};
                    ~AliVariableExpression() {}
   virtual Bool_t    Value( TObjArray& pgm );
  virtual TString    Unparse() const { return fVname; }

private:
          TString    fVname;   // Variable name

   ClassDef( AliVariableExpression, 1 )  // Class to define a variable expression
};

#endif
