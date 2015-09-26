// Written By James McGuigan - james@starsfaq.com
// Packet Location Calculator v1.0.1
// GUI Code written using Borland Builder v3

//---------------------------------------------------------------------------
#include <vcl.h>
#include <math.h>
#include "PLCU.h"
#pragma hdrstop


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
  : TForm(Owner)
{
  WarpBoxFocus = true;
  Warp = 0;
  HalfSpeedFirstYear = false;
  FormGNU = new TFormGNU(this);
  ReachedTarget = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::EditObjectSpeedChange(TObject *Sender)
{
  EditSpeedLY->Text = AnsiString(EditObjectSpeed->Text.ToIntDef(0) *
                                 EditObjectSpeed->Text.ToIntDef(0));

  DistanceCalc(this);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::EditSpeedLYChange(TObject *Sender)
{
  Warp = sqrt(EditSpeedLY->Text.ToInt());

  if(floor(Warp + 0.99999) != floor(Warp)) // if warp is not a whole number
  {
    EditObjectSpeedCover->Text = "";
    EditObjectSpeedCover->Visible = true;
    EditObjectSpeed->Visible = false;
  }
  else
  {
    EditObjectSpeedCover->Text = "";
    EditObjectSpeedCover->Visible = false;
    EditObjectSpeed->Visible = true;
    EditObjectSpeed->Text = AnsiString(int(Warp));
    WarpBoxFocus = true;
  }

  DistanceCalc(this);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::UpDown5Click(TObject *Sender, TUDBtnType Button)
{
  WarpBoxFocus = true;
  EditObjectSpeedCover->Text = "";
  EditObjectSpeedCover->Visible = false;
  EditObjectSpeed->Visible = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::EditObjectSpeedCoverChange(TObject *Sender)
{
  EditObjectSpeedCover->Visible = false;
  EditObjectSpeed->Visible = true;
  WarpBoxFocus = true;
  EditObjectSpeed->SetFocus();
  EditObjectSpeedChange(this);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CheckBoxHalfSpeedClick(TObject *Sender)
{
  HalfSpeedFirstYear = CheckBoxHalfSpeed->Checked;
  DistanceCalc(this);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::DistanceCalc(TObject *Sender)
{
  int DistanceX;
  int DistanceY;
  int StartX;
  int StartY;
  int StartDistanceX;
  int StartDistanceY;
  int StartDistance;
  int ModX = 0;
  int ModY = 0;
  int Years = 0;
  float prevDistance;
  float TravelSpeed = 0;
  int saveModX = 0;
  int saveModY = 0;
  int saveYears = -1;
  bool SavedMod = false;

  StartDistanceX = EditEndX->Text.ToIntDef(0) - EditStartX->Text.ToIntDef(0);
  StartDistanceY = EditEndY->Text.ToIntDef(0) - EditStartY->Text.ToIntDef(0);
  if(StartDistanceX != 0 || StartDistanceY != 0)
    StartDistance = sqrt(StartDistanceX*StartDistanceX + StartDistanceY*StartDistanceY);

  LabelDistance->Caption = AnsiString(floor(StartDistance));

  if(RadioButtonA_X_B->Checked == true)
  {
    // if A -> ??? -> B
    StartX = EditStartX->Text.ToIntDef(0);
    StartY = EditStartY->Text.ToIntDef(0);
  }
  else
  {
    // if A -> B -> ???
    StartX = EditEndX->Text.ToIntDef(0);
    StartY = EditEndY->Text.ToIntDef(0);
  }


  if(StartDistance != 0)
  {
    // Calculate Movement for each year of travel
    while(SavedMod  == false
       || saveYears == -1)
    {
      Years++;
      prevDistance = Distance;

      // Work Out Current Location
      DistanceX = (EditEndX->Text.ToIntDef(0)) - (EditStartX->Text.ToIntDef(0) + ModX);
      DistanceY = (EditEndY->Text.ToIntDef(0)) - (EditStartY->Text.ToIntDef(0) + ModY);

      if(DistanceY == 0 && DistanceX == 0)
        Distance = 0;
      else
        Distance = sqrt(DistanceY*DistanceY + DistanceX*DistanceX);

      // Reduce travel speed in first year if box is ticked
      TravelSpeed = EditSpeedLY->Text.ToIntDef(0);
      if(HalfSpeedFirstYear == true && Years == 1)
        TravelSpeed = floor(TravelSpeed / 2);

      // bug - Calculating several years travel beyond reference point, when
      //       distance was an exact multiple of warp speed would cause a
      //       divide by zero error.
      //
      ModX += floor(StartDistanceX * (TravelSpeed / StartDistance) + 0.5);
      ModY += floor(StartDistanceY * (TravelSpeed / StartDistance) + 0.5);

      // save distance traveled after specified travel time is up
      if(Years == EditTime->Text.ToIntDef(0))
      {
        saveModX = ModX;
        saveModY = ModY;
        SavedMod = true;
      }

      // Hack to ensure loop gets past second iterations
      if(Years == 2 && HalfSpeedFirstYear == true)
        TravelSpeed = TravelSpeed / 2;

      if(Distance == 0 // check if object has reached location exactly
      || (prevDistance - TravelSpeed - 1 > Distance // check if object has overshot the target
        ||prevDistance - TravelSpeed + 1 < Distance)// +-1 range to account for rounding errors
      && saveYears == -1  // check the time hasn't already been saved
      && Years != 1)      // No movement is recorded in the first year
      {
        saveYears = Years -1;
      }

    }
  }
  else // if distance == 0
  {
    saveYears = 0;
  }

  LabelOutput->Caption = "Object will be at   X: " + AnsiString(StartX+saveModX)
     + "   Y: " + AnsiString(StartY+saveModY) + "   in " + EditTime->Text
     + " year" + ((EditTime->Text != 1) ? "s" : "");

  if(RadioButtonA_X_B->Checked == true)
  {
    LabelETA->Caption = "Object will take " + AnsiString(saveYears) + " year"
       + ((saveYears > 1) ? "s" : "") + " to reach location B";
  }
  else
  {
    LabelETA->Caption = "";
  }

//  if(EditTime->Text != 1)
//    LabelOutput->Caption = LabelOutput->Caption + "s";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CheckBoxStayOnTopClick(TObject *Sender)
{
  // Bug-fix - clicking this button resets user data - so save and restore data
  String saveEditStartX  = EditStartX->Text;
  String saveEditStartY  = EditStartY->Text;
  String saveEditEndX    = EditEndX->Text;
  String saveEditEndY    = EditEndY->Text;
  String saveEditSpeedLY = EditSpeedLY->Text;
  String saveEditTime    = EditTime->Text;

  if(CheckBoxStayOnTop->Checked == true)
    Form1->FormStyle = fsStayOnTop;
  else
    Form1->FormStyle = fsNormal;

  EditStartX->Text  = saveEditStartX;
  EditStartY->Text  = saveEditStartY;
  EditEndX->Text    = saveEditEndX;
  EditEndY->Text    = saveEditEndY;
  EditSpeedLY->Text = saveEditSpeedLY;
  EditTime->Text    = saveEditTime;

  DistanceCalc(this);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::EditObjectSpeedClick(TObject *Sender)
{
  WarpBoxFocus = true;
  EditObjectSpeedCover->Text = "";
  EditObjectSpeedCover->Visible = false;
  EditObjectSpeed->Visible = true;

  EditObjectSpeedChange(this);  
}
//---------------------------------------------------------------------------
void __fastcall TForm1::EditObjectSpeedMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  WarpBoxFocus = true;
  EditObjectSpeedChange(this);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::UpDown7MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  if(floor(Warp + 0.99999) != floor(Warp))
    WarpBoxFocus = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::EditSpeedLYClick(TObject *Sender)
{
  WarpBoxFocus = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormPaint(TObject *Sender)
{
  Form1->Canvas->MoveTo(ShapeA1->Left + ShapeA1->Width/2,ShapeA1->Top + ShapeA1->Height/2);
  Form1->Canvas->LineTo(ShapeB1->Left + ShapeB1->Width/2,ShapeB1->Top + ShapeB1->Height/2);

  Form1->Canvas->MoveTo(ShapeA2->Left + ShapeA2->Width/2,ShapeA2->Top + ShapeA2->Height/2);
  Form1->Canvas->LineTo(ShapeX2->Left + ShapeX2->Width/2,ShapeX2->Top + ShapeX2->Height/2);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
    FormGNU->Show();
}
//---------------------------------------------------------------------------



