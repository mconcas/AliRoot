//
// *** Class AliRsnPair ***
//
// TODO
//
// authors: A. Pulvirenti (email: alberto.pulvirenti@ct.infn.it)
//          M. Vala (email: martin.vala@cern.ch)
//

#ifndef ALIRSNPAIR_H
#define ALIRSNPAIR_H

#include "TNamed.h"
#include "TClonesArray.h"

#include "AliRsnDaughter.h"
#include "AliRsnPairDef.h"
#include "AliRsnMother.h"
#include "AliRsnCutManager.h"

class TH1;
class TH2;
class TList;
class TArrayI;

class AliRsnEvent;
class AliRsnCutSet;
class AliRsnFunction;
class AliRsnValue;

class AliRsnPair : public TNamed
{
  public:

    AliRsnPair(const char *name = "default", AliRsnPairDef *def = 0);
    AliRsnPair(const AliRsnPair &copy);
    AliRsnPair& operator=(const AliRsnPair&);
    ~AliRsnPair();

    void    SetOnlyTrue(Bool_t onlyTrue = kTRUE) {fOnlyTrue = onlyTrue;}

    void    Print(Option_t *option = "") const;
    void    SetMixed(Bool_t doit = kTRUE) {fIsMixed = doit;}
    Bool_t  IsMixed() const {return fIsMixed;}
    
    AliRsnCutManager* GetCutManager() {return &fCutManager;}
    AliRsnMother*     GetMother() {return &fMother;}
    AliRsnPairDef*    GetPairDef() {return fPairDef;}
    Bool_t            Fill(AliRsnDaughter *d0, AliRsnDaughter *d1, AliRsnEvent *ev1, AliRsnEvent *ev2);
    virtual void      Compute();
    virtual void      Init(const char *prefix, TList *list);

  protected:

    Bool_t            fOnlyTrue;        //  select true pairs only?
    Bool_t            fIsMixed;         //  is this an event-mixing?

    AliRsnPairDef    *fPairDef;         //  pair definition (particles, charges)
    AliRsnCutManager  fCutManager;      //  collection of all cuts
    AliRsnMother      fMother;          //  mother candidate (to avoid creating it continuously)
    AliRsnEvent      *fEvent;           //  pointer to current event
    
  private:

    ClassDef(AliRsnPair, 2)
};

#endif

