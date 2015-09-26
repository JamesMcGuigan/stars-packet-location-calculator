// Written By James McGuigan - james@starsfaq.com
// Packet Location Calculator v1.0.1

//---------------------------------------------------------------------------
#ifndef PLCUH
#define PLCUH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include "GNU.h"
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
  TLabel *Label1;
  TLabel *Label2;
  TUpDown *UpDown1;
  TEdit *EditStartX;
  TEdit *EditEndX;
  TEdit *EditStartY;
  TEdit *EditEndY;
  TLabel *Label3;
  TLabel *Label4;
  TLabel *Label5;
  TLabel *Label6;
  TUpDown *UpDown2;
  TUpDown *UpDown3;
  TUpDown *UpDown4;
  TLabel *Label7;
  TEdit *EditObjectSpeed;
  TUpDown *UpDown5;
  TLabel *Label8;
  TEdit *EditTime;
  TUpDown *UpDown6;
  TLabel *Label9;
  TEdit *EditSpeedLY;
  TCheckBox *CheckBoxHalfSpeed;
  TUpDown *UpDown7;
  TLabel *Label10;
  TLabel *LabelDistance;
  TLabel *Label11;
  TLabel *LabelOutput;
  TLabel *Label12;
  TLabel *Label13;
  TLabel *Label14;
  TLabel *Label15;
  TLabel *Label16;
  TLabel *Label17;
  TRadioButton *RadioButtonA_X_B;
  TRadioButton *RadioButton2;
  TShape *ShapeA1;
  TShape *ShapeX1;
  TShape *ShapeB1;
  TShape *ShapeX2;
  TShape *ShapeB2;
  TShape *ShapeA2;
  TEdit *EditObjectSpeedCover;
  TLabel *Label18;
  TLabel *Label19;
  TLabel *Label20;
  TLabel *Label21;
  TLabel *Label23;
  TLabel *Label24;
  TPanel *Panel1;
  TLabel *Label22;
  TLabel *Label25;
  TButton *Button1;
  TPanel *Panel2;
  TCheckBox *CheckBoxStayOnTop;
    TLabel *Label26;
  TLabel *LabelETA;
  void __fastcall EditObjectSpeedChange(TObject *Sender);
  void __fastcall EditSpeedLYChange(TObject *Sender);
  void __fastcall UpDown5Click(TObject *Sender, TUDBtnType Button);
  void __fastcall EditObjectSpeedCoverChange(TObject *Sender);
  void __fastcall CheckBoxHalfSpeedClick(TObject *Sender);
  void __fastcall DistanceCalc(TObject *Sender);
  void __fastcall FormPaint(TObject *Sender);
  void __fastcall CheckBoxStayOnTopClick(TObject *Sender);
  void __fastcall EditObjectSpeedClick(TObject *Sender);
  void __fastcall EditObjectSpeedMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
  void __fastcall UpDown7MouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
  void __fastcall EditSpeedLYClick(TObject *Sender);
  void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
  float Distance;
  float Warp;
  bool WarpBoxFocus;
  bool HalfSpeedFirstYear;
  bool ReachedTarget;  
  TFormGNU* FormGNU;

public:		// User declarations
  __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
