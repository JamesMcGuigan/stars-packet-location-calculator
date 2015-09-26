//---------------------------------------------------------------------------
#ifndef GNUH
#define GNUH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFormGNU : public TForm
{
__published:	// IDE-managed Components
    TLabel *Label22;
    TLabel *Label25;
    TPanel *Panel1;
    TMemo *Memo1;
    TLabel *Label1;
private:	// User declarations
public:		// User declarations
    __fastcall TFormGNU(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormGNU *FormGNU;
//---------------------------------------------------------------------------
#endif
