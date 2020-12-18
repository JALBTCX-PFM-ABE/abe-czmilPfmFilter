
/*********************************************************************************************

    This is public domain software that was developed by or for the U.S. Naval Oceanographic
    Office and/or the U.S. Army Corps of Engineers.

    This is a work of the U.S. Government. In accordance with 17 USC 105, copyright protection
    is not available for any work of the U.S. Government.

    Neither the United States Government, nor any employees of the United States Government,
    nor the author, makes any warranty, express or implied, without even the implied warranty
    of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE, or assumes any liability or
    responsibility for the accuracy, completeness, or usefulness of any information,
    apparatus, product, or process disclosed, or represents that its use would not infringe
    privately-owned rights. Reference herein to any specific commercial products, process,
    or service by trade name, trademark, manufacturer, or otherwise, does not necessarily
    constitute or imply its endorsement, recommendation, or favoring by the United States
    Government. The views and opinions of authors expressed herein do not necessarily state
    or reflect those of the United States Government, and shall not be used for advertising
    or product endorsement purposes.
*********************************************************************************************/


/****************************************  IMPORTANT NOTE  **********************************

    Comments in this file that start with / * ! or / / ! are being used by Doxygen to
    document the software.  Dashes in these comment blocks are used to create bullet lists.
    The lack of blank lines after a block of dash preceeded comments means that the next
    block of dash preceeded comments is a new, indented bullet list.  I've tried to keep the
    Doxygen formatting to a minimum but there are some other items (like <br> and <pre>)
    that need to be left alone.  If you see a comment that starts with / * ! or / / ! and
    there is something that looks a bit weird it is probably due to some arcane Doxygen
    syntax.  Be very careful modifying blocks of Doxygen comments.

*****************************************  IMPORTANT NOTE  **********************************/



#include "optionPage.hpp"
#include "optionPageHelp.hpp"

optionPage::optionPage (QWidget *parent, OPTIONS *op):
  QWizardPage (parent)
{
  options = op;


  setTitle (tr ("Filter options"));

  setPixmap (QWizard::WatermarkPixmap, QPixmap(":/icons/czmilPfmFilterWatermark.png"));


  QVBoxLayout *vbox = new QVBoxLayout (this);
  vbox->setMargin (5);
  vbox->setSpacing (5);
  QHBoxLayout *hbox = new QHBoxLayout;
  vbox->addLayout (hbox);


  lbox[0] = new QGroupBox (tr ("First level bathy filter options"), this);
  lboxLayout[0] = new QHBoxLayout;
  lbox[0]->setLayout (lboxLayout[0]);


  dbox[0] = new QGroupBox (tr ("Density cutoff"), this);
  dboxLayout[0] = new QHBoxLayout;
  dbox[0]->setLayout (dboxLayout[0]);
  density[0] = new QLineEdit ("1.0", dbox[0]);
  density[0]->setAlignment (Qt::AlignCenter);
  QString dens;
  dens.sprintf ("%0.1f", options->density[0]);
  density[0]->setText (dens);
  density[0]->setToolTip (tr ("Data density value"));
  density[0]->setWhatsThis (densityText0);
  dboxLayout[0]->addWidget (density[0]);
  lboxLayout[0]->addWidget (dbox[0]);

  rbox[0] = new QGroupBox (tr ("Radius"), this);
  rboxLayout[0] = new QHBoxLayout;
  rbox[0]->setLayout (rboxLayout[0]);
  hpRadiusValue[0] = new QLineEdit ("1.0", rbox[0]);
  hpRadiusValue[0]->setAlignment (Qt::AlignCenter);
  QString rad;
  rad.sprintf ("%0.2f", options->hpRadius[0]);
  hpRadiusValue[0]->setText (rad);
  hpRadiusValue[0]->setToolTip (tr ("Filter radius value"));
  hpRadiusValue[0]->setWhatsThis (hpRadiusValueText0);
  rboxLayout[0]->addWidget (hpRadiusValue[0]);
  lboxLayout[0]->addWidget (rbox[0]);

  htbox[0] = new QGroupBox (tr ("Height"), this);
  htboxLayout[0] = new QHBoxLayout;
  htbox[0]->setLayout (htboxLayout[0]);
  hpHeightValue[0] = new QLineEdit ("1.0", htbox[0]);
  hpHeightValue[0]->setAlignment (Qt::AlignCenter);
  QString ht;
  ht.sprintf ("%0.2f", options->hpHeight[0]);
  hpHeightValue[0]->setText (ht);
  hpHeightValue[0]->setToolTip (tr ("Filter height value"));
  hpHeightValue[0]->setWhatsThis (hpHeightValueText0);
  htboxLayout[0]->addWidget (hpHeightValue[0]);
  lboxLayout[0]->addWidget (htbox[0]);

  sbox[0] = new QGroupBox (tr ("Single line neighbors"), this);
  sboxLayout[0] = new QHBoxLayout;
  sbox[0]->setLayout (sboxLayout[0]);
  hpNeighborsValue[0] = new QLineEdit (" 000 ", sbox[0]);
  hpNeighborsValue[0]->setAlignment (Qt::AlignCenter);
  QString nb;
  nb.sprintf ("%d", options->hpNeighbors[0]);
  hpNeighborsValue[0]->setText (nb);
  hpNeighborsValue[0]->setToolTip (tr ("Filter single line neighbors value"));
  hpNeighborsValue[0]->setWhatsThis (hpNeighborsValueText0);
  sboxLayout[0]->addWidget (hpNeighborsValue[0]);
  lboxLayout[0]->addWidget (sbox[0]);


  mbox[0] = new QGroupBox (tr ("Multi-line neighbors"), this);
  mboxLayout[0] = new QHBoxLayout;
  mbox[0]->setLayout (mboxLayout[0]);
  hpMultiNeighborsValue[0] = new QLineEdit (" 000 ", mbox[0]);
  hpMultiNeighborsValue[0]->setAlignment (Qt::AlignCenter);
  nb.sprintf ("%d", options->hpMultiNeighbors[0]);
  hpMultiNeighborsValue[0]->setText (nb);
  hpMultiNeighborsValue[0]->setToolTip (tr ("Hockey Puck filter multi-line neighbors value"));
  hpMultiNeighborsValue[0]->setWhatsThis (hpMultiNeighborsValueText0);
  mboxLayout[0]->addWidget (hpMultiNeighborsValue[0]);
  lboxLayout[0]->addWidget (mbox[0]);


  vbox->addWidget (lbox[0]);


  lbox[1] = new QGroupBox (tr ("Second level bathy filter options"), this);
  lboxLayout[1] = new QHBoxLayout;
  lbox[1]->setLayout (lboxLayout[1]);


  dbox[1] = new QGroupBox (tr ("Density cutoff"), this);
  dboxLayout[1] = new QHBoxLayout;
  dbox[1]->setLayout (dboxLayout[1]);
  density[1] = new QLineEdit ("1.0", dbox[1]);
  density[1]->setAlignment (Qt::AlignCenter);
  dens.sprintf ("%0.1f", options->density[1]);
  density[1]->setText (dens);
  density[1]->setToolTip (tr ("Data density value"));
  density[1]->setWhatsThis (densityText1);
  dboxLayout[1]->addWidget (density[1]);
  lboxLayout[1]->addWidget (dbox[1]);

  rbox[1] = new QGroupBox (tr ("Radius"), this);
  rboxLayout[1] = new QHBoxLayout;
  rbox[1]->setLayout (rboxLayout[1]);
  hpRadiusValue[1] = new QLineEdit ("1.0", rbox[1]);
  hpRadiusValue[1]->setAlignment (Qt::AlignCenter);
  rad.sprintf ("%0.2f", options->hpRadius[1]);
  hpRadiusValue[1]->setText (rad);
  hpRadiusValue[1]->setToolTip (tr ("Filter radius value"));
  hpRadiusValue[1]->setWhatsThis (hpRadiusValueText1);
  rboxLayout[1]->addWidget (hpRadiusValue[1]);
  lboxLayout[1]->addWidget (rbox[1]);

  htbox[1] = new QGroupBox (tr ("Height"), this);
  htboxLayout[1] = new QHBoxLayout;
  htbox[1]->setLayout (htboxLayout[1]);
  hpHeightValue[1] = new QLineEdit ("1.0", htbox[1]);
  hpHeightValue[1]->setAlignment (Qt::AlignCenter);
  ht.sprintf ("%0.2f", options->hpHeight[1]);
  hpHeightValue[1]->setText (ht);
  hpHeightValue[1]->setToolTip (tr ("Filter height value"));
  hpHeightValue[1]->setWhatsThis (hpHeightValueText1);
  htboxLayout[1]->addWidget (hpHeightValue[1]);
  lboxLayout[1]->addWidget (htbox[1]);

  sbox[1] = new QGroupBox (tr ("Single line neighbors"), this);
  sboxLayout[1] = new QHBoxLayout;
  sbox[1]->setLayout (sboxLayout[1]);
  hpNeighborsValue[1] = new QLineEdit (" 000 ", sbox[1]);
  hpNeighborsValue[1]->setAlignment (Qt::AlignCenter);
  nb.sprintf ("%d", options->hpNeighbors[1]);
  hpNeighborsValue[1]->setText (nb);
  hpNeighborsValue[1]->setToolTip (tr ("Filter single line neighbors value"));
  hpNeighborsValue[1]->setWhatsThis (hpNeighborsValueText1);
  sboxLayout[1]->addWidget (hpNeighborsValue[1]);
  lboxLayout[1]->addWidget (sbox[1]);


  mbox[1] = new QGroupBox (tr ("Multi-line neighbors"), this);
  mboxLayout[1] = new QHBoxLayout;
  mbox[1]->setLayout (mboxLayout[1]);
  hpMultiNeighborsValue[1] = new QLineEdit (" 000 ", mbox[1]);
  hpMultiNeighborsValue[1]->setAlignment (Qt::AlignCenter);
  nb.sprintf ("%d", options->hpMultiNeighbors[1]);
  hpMultiNeighborsValue[1]->setText (nb);
  hpMultiNeighborsValue[1]->setToolTip (tr ("Hockey Puck filter multi-line neighbors value"));
  hpMultiNeighborsValue[1]->setWhatsThis (hpMultiNeighborsValueText1);
  mboxLayout[1]->addWidget (hpMultiNeighborsValue[1]);
  lboxLayout[1]->addWidget (mbox[1]);


  vbox->addWidget (lbox[1]);


  lbox[2] = new QGroupBox (tr ("Topo filter options"), this);
  lboxLayout[2] = new QHBoxLayout;
  lbox[2]->setLayout (lboxLayout[2]);


  rbox[2] = new QGroupBox (tr ("Radius"), this);
  rboxLayout[2] = new QHBoxLayout;
  rbox[2]->setLayout (rboxLayout[2]);
  hpRadiusValue[2] = new QLineEdit ("1.0", rbox[2]);
  hpRadiusValue[2]->setAlignment (Qt::AlignCenter);
  rad.sprintf ("%0.2f", options->hpRadius[2]);
  hpRadiusValue[2]->setText (rad);
  hpRadiusValue[2]->setToolTip (tr ("Filter radius value"));
  hpRadiusValue[2]->setWhatsThis (hpRadiusValueText2);
  rboxLayout[2]->addWidget (hpRadiusValue[2]);
  lboxLayout[2]->addWidget (rbox[2]);

  htbox[2] = new QGroupBox (tr ("Height"), this);
  htboxLayout[2] = new QHBoxLayout;
  htbox[2]->setLayout (htboxLayout[2]);
  hpHeightValue[2] = new QLineEdit ("1.0", htbox[2]);
  hpHeightValue[2]->setAlignment (Qt::AlignCenter);
  ht.sprintf ("%0.2f", options->hpHeight[2]);
  hpHeightValue[2]->setText (ht);
  hpHeightValue[2]->setToolTip (tr ("Filter height value"));
  hpHeightValue[2]->setWhatsThis (hpHeightValueText2);
  htboxLayout[2]->addWidget (hpHeightValue[2]);
  lboxLayout[2]->addWidget (htbox[2]);

  sbox[2] = new QGroupBox (tr ("Single line neighbors"), this);
  sboxLayout[2] = new QHBoxLayout;
  sbox[2]->setLayout (sboxLayout[2]);
  hpNeighborsValue[2] = new QLineEdit (" 000 ", sbox[2]);
  hpNeighborsValue[2]->setAlignment (Qt::AlignCenter);
  nb.sprintf ("%d", options->hpNeighbors[2]);
  hpNeighborsValue[2]->setText (nb);
  hpNeighborsValue[2]->setToolTip (tr ("Filter single line neighbors value"));
  hpNeighborsValue[2]->setWhatsThis (hpNeighborsValueText2);
  sboxLayout[2]->addWidget (hpNeighborsValue[2]);
  lboxLayout[2]->addWidget (sbox[2]);


  mbox[2] = new QGroupBox (tr ("Multi-line neighbors"), this);
  mboxLayout[2] = new QHBoxLayout;
  mbox[2]->setLayout (mboxLayout[2]);
  hpMultiNeighborsValue[2] = new QLineEdit (" 000 ", mbox[2]);
  hpMultiNeighborsValue[2]->setAlignment (Qt::AlignCenter);
  nb.sprintf ("%d", options->hpMultiNeighbors[2]);
  hpMultiNeighborsValue[2]->setText (nb);
  hpMultiNeighborsValue[2]->setToolTip (tr ("Hockey Puck filter multi-line neighbors value"));
  hpMultiNeighborsValue[2]->setWhatsThis (hpMultiNeighborsValueText2);
  mboxLayout[2]->addWidget (hpMultiNeighborsValue[2]);
  lboxLayout[2]->addWidget (mbox[2]);


  vbox->addWidget (lbox[2]);


  QGroupBox *invBox = new QGroupBox (tr ("Invalidate"), this);
  QHBoxLayout *invBoxLayout = new QHBoxLayout;
  invBox->setLayout (invBoxLayout);


  inv = new QCheckBox (invBox);
  inv->setToolTip (tr ("Check this box if you want to invalidate points instead of marking as suspect"));
  inv->setWhatsThis (invText);
  connect (inv, SIGNAL (stateChanged (int)), this, SLOT (slotInvClicked (int)));
  invBoxLayout->addWidget (inv);
  inv->setChecked (options->invalidate);


  vbox->addWidget (invBox);


  registerField ("density0", density[0]);
  registerField ("hpRadiusValue0", hpRadiusValue[0]);
  registerField ("hpHeightValue0", hpHeightValue[0]);
  registerField ("hpNeighborsValue0", hpNeighborsValue[0]);
  registerField ("hpMultiNeighborsValue0", hpMultiNeighborsValue[0]);
  registerField ("density1", density[1]);
  registerField ("hpRadiusValue1", hpRadiusValue[1]);
  registerField ("hpHeightValue1", hpHeightValue[1]);
  registerField ("hpNeighborsValue1", hpNeighborsValue[1]);
  registerField ("hpMultiNeighborsValue1", hpMultiNeighborsValue[1]);
  registerField ("hpRadiusValue2", hpRadiusValue[2]);
  registerField ("hpHeightValue2", hpHeightValue[2]);
  registerField ("hpNeighborsValue2", hpNeighborsValue[2]);
  registerField ("hpMultiNeighborsValue2", hpMultiNeighborsValue[2]);
}



void 
optionPage::setFileCenter (QString file)
{
  int32_t pfm_handle;
  PFM_OPEN_ARGS open_args;

  strcpy (open_args.list_path, file.toLatin1 ());

  open_args.checkpoint = 0;
  if ((pfm_handle = open_existing_pfm_file (&open_args)) < 0) pfm_error_exit (pfm_error);

  mbr_center.y = open_args.head.mbr.min_y + (open_args.head.mbr.max_y - open_args.head.mbr.min_y) / 2.0;
  mbr_center.x = open_args.head.mbr.min_x + (open_args.head.mbr.max_x - open_args.head.mbr.min_x) / 2.0;

  close_pfm_file (pfm_handle);
}



bool 
optionPage::validatePage ()
{
  return (true);
}



void
optionPage::slotInvClicked (int state)
{
  if (!state)
    {
      options->invalidate = NVFalse;
    }
  else
    {
      options->invalidate = NVTrue;
    }
}



void
optionPage::slotHelp ()
{
  QWhatsThis::enterWhatsThisMode ();
}
