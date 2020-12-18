
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



#include "czmilPfmFilter.hpp"
#include "czmilPfmFilterHelp.hpp"

#include <getopt.h>

double settings_version = 1.0;


czmilPfmFilter::czmilPfmFilter (int32_t *argc, char **argv, QWidget *parent)
  : QWizard (parent, 0)
{
  QResource::registerResource ("/icons.rcc");


  //  Set the main icon

  setWindowIcon (QIcon (":/icons/czmilPfmFilterWatermark.png"));


  //  Get the command line arguments.  This is a placeholder.

  int32_t option_index = 0;

  while (NVTrue) 
    {
      static struct option long_options[] = {{"dummy", no_argument, 0, 0},
                                             {0, no_argument, 0, 0}};

      char c = (char) getopt_long (*argc, argv, "d", long_options, &option_index);
      if (c == -1) break;

      switch (c) 
        {
        case 0:

          switch (option_index)
            {
            case 0:
              //  dummy
              break;
            }
          break;

        case 'd':
          //  dummy
          break;
        }
    }


  //  Get the user's defaults if available

  envin (&options);


  // Set the application font

  QApplication::setFont (options.font);


  options.replace = NVTrue;


  setWizardStyle (QWizard::ClassicStyle);


  setOption (HaveHelpButton, true);
  setOption (ExtendedWatermarkPixmap, false);

  connect (this, SIGNAL (helpRequested ()), this, SLOT (slotHelpClicked ()));


  //  Set the window size and location from the defaults

  this->resize (options.window_width, options.window_height);
  this->move (options.window_x, options.window_y);


  setPage (0, new startPage (argc, argv, this, &options));

  setPage (1, oPage = new optionPage (this, &options));

  setPage (2, new runPage (this, &progress));


  setButtonText (QWizard::CustomButton1, tr("&Run"));
  setOption (QWizard::HaveCustomButton1, true);
  button (QWizard::CustomButton1)->setToolTip (tr ("Start filtering the PFM"));
  button (QWizard::CustomButton1)->setWhatsThis (runText);
  connect (this, SIGNAL (customButtonClicked (int)), this, SLOT (slotCustomButtonClicked (int)));


  setStartId (0);
}



czmilPfmFilter::~czmilPfmFilter ()
{
}



void czmilPfmFilter::initializePage (int id)
{
  button (QWizard::HelpButton)->setIcon (QIcon (":/icons/contextHelp.png"));
  button (QWizard::CustomButton1)->setEnabled (false);


  switch (id)
    {
    case 0:
      break;

    case 1:
      pfm_file = field ("pfm_file_edit").toString ();
      area_file = field ("area_file_edit").toString ();
      ex_file = field ("ex_file_edit").toString ();
      oPage->setFileCenter (pfm_file);
      break;

    case 2:
      button (QWizard::CustomButton1)->setEnabled (true);


      options.density[0] = field ("density0").toDouble ();
      options.hpRadius[0] = field ("hpRadiusValue0").toDouble ();
      options.hpHeight[0] = field ("hpHeightValue0").toDouble ();
      options.hpNeighbors[0] = field ("hpNeighborsValue0").toInt ();
      options.hpMultiNeighbors[0] = field ("hpMultiNeighborsValue0").toInt ();

      options.density[1] = field ("density1").toDouble ();
      options.hpRadius[1] = field ("hpRadiusValue1").toDouble ();
      options.hpHeight[1] = field ("hpHeightValue1").toDouble ();
      options.hpNeighbors[1] = field ("hpNeighborsValue1").toInt ();
      options.hpMultiNeighbors[1] = field ("hpMultiNeighborsValue1").toInt ();

      options.hpRadius[2] = field ("hpRadiusValue2").toDouble ();
      options.hpHeight[2] = field ("hpHeightValue2").toDouble ();
      options.hpNeighbors[2] = field ("hpNeighborsValue2").toInt ();
      options.hpMultiNeighbors[2] = field ("hpMultiNeighborsValue2").toInt ();


      //  Use frame geometry to get the absolute x and y.

      QRect tmp = this->frameGeometry ();
      options.window_x = tmp.x ();
      options.window_y = tmp.y ();


      //  Use geometry to get the width and height.

      tmp = this->geometry ();
      options.window_width = tmp.width ();
      options.window_height = tmp.height ();


      //  Save the options.

      envout (&options);


      QString string;

      progress.list->clear ();

      string = tr ("PFM file : ") + pfm_file;
      progress.list->addItem (string);

      if (!area_file.isEmpty ())
        {
          string = tr ("Area file : ") + area_file;
          progress.list->addItem (string);
        }

      if (!ex_file.isEmpty ())
        {
          string = tr ("Exclusion area file : ") + ex_file;
          progress.list->addItem (string);
        }



      string.sprintf (tr ("Bathy level 1 Density cutoff = %.2f").toLatin1 (), options.density[0]);
      progress.list->addItem (string);

      string.sprintf (tr ("Bathy level 1 Filter radius = %.2f").toLatin1 (), options.hpRadius[0]);
      progress.list->addItem (string);

      string.sprintf (tr ("Bathy level 1 Filter height = %.2f").toLatin1 (), options.hpHeight[0]);
      progress.list->addItem (string);

      if (!options.hpNeighbors[0])
        {
          string = tr ("Bathy level 1 - Only multiple line coverage areas will be filtered.");
          progress.list->addItem (string);
        }
      else
        {
          string.sprintf (tr ("Bathy level 1 Required single line neighbors = %d").toLatin1 (), options.hpNeighbors[0]);
          progress.list->addItem (string);
        }

      string.sprintf (tr ("Bathy level 1 Required multi-line neighbors = %d").toLatin1 (), options.hpMultiNeighbors[0]);
      progress.list->addItem (string);


      string.sprintf (tr ("Bathy level 2 Density cutoff = %.2f").toLatin1 (), options.density[1]);
      progress.list->addItem (string);

      string.sprintf (tr ("Bathy level 2 Filter radius = %.2f").toLatin1 (), options.hpRadius[1]);
      progress.list->addItem (string);

      string.sprintf (tr ("Bathy level 2 Filter height = %.2f").toLatin1 (), options.hpHeight[1]);
      progress.list->addItem (string);

      if (!options.hpNeighbors[1])
        {
          string = tr ("Bathy level 2 - Only multiple line coverage areas will be filtered.");
          progress.list->addItem (string);
        }
      else
        {
          string.sprintf (tr ("Bathy level 2 Required single line neighbors = %d").toLatin1 (), options.hpNeighbors[1]);
          progress.list->addItem (string);
        }

      string.sprintf (tr ("Bathy level 2 Required multi-line neighbors = %d").toLatin1 (), options.hpMultiNeighbors[1]);
      progress.list->addItem (string);


      string.sprintf (tr ("Topo Filter radius = %.2f").toLatin1 (), options.hpRadius[2]);
      progress.list->addItem (string);

      string.sprintf (tr ("Topo Filter height = %.2f").toLatin1 (), options.hpHeight[2]);
      progress.list->addItem (string);

      if (!options.hpNeighbors[1])
        {
          string = tr ("Topo - Only multiple line coverage areas will be filtered.");
          progress.list->addItem (string);
        }
      else
        {
          string.sprintf (tr ("Topo Required single line neighbors = %d").toLatin1 (), options.hpNeighbors[2]);
          progress.list->addItem (string);
        }

      string.sprintf (tr ("Topo Required multi-line neighbors = %d").toLatin1 (), options.hpMultiNeighbors[2]);
      progress.list->addItem (string);

      break;
    }
}



void czmilPfmFilter::cleanupPage (int id)
{
  switch (id)
    {
    case 0:
      break;

    case 1:
      break;

    case 2:
      break;
    }
}



void czmilPfmFilter::slotHelpClicked ()
{
  QWhatsThis::enterWhatsThisMode ();
}



//  This is where the fun stuff happens.

void 
czmilPfmFilter::slotCustomButtonClicked (int id __attribute__ ((unused)))
{
  filterThread        filter_thread[FILTER_THREADS];
  static int32_t      old_percent = -1;
  QString             qstring;


  QApplication::setOverrideCursor (Qt::WaitCursor);


  button (QWizard::FinishButton)->setEnabled (false);
  button (QWizard::BackButton)->setEnabled (false);
  button (QWizard::CustomButton1)->setEnabled (false);


  //  We open a different handle for each thread so that we don't have any collision problems in the PFM library.

  for (int32_t i = 0 ; i < FILTER_THREADS ; i++)
    {
      strcpy (open_args[i].list_path, pfm_file.toLatin1 ());


      //  Open the PFM file.

      open_args[i].checkpoint = 0;
      if ((pfm_handle[i] = open_existing_pfm_file (&open_args[i])) < 0) pfm_error_exit (pfm_error);

      int32_t row_size = NINT (open_args[i].head.bin_height / FILTER_THREADS);

      start_row[i] = i * row_size;
      end_row[i] = qMin ((i + 1) * row_size - 1, open_args[i].head.bin_height - 1);
    }


  //  Check for an exclusion area file.

  options.ex_polygon_count = 0;
  if (!ex_file.isEmpty ())
    {
      char ef[512];
      strcpy (ef, ex_file.toLatin1 ());

      get_area_mbr (ef, &options.ex_polygon_count, options.ex_polygon_x, options.ex_polygon_y, &options.ex_mbr);


      //  Convert the polygon to the pseudo X/Y that we will be using in the filter threads (we don't have to worry about the MBR
      //  because we don't use it).

      for (int32_t i = 0 ; i < options.ex_polygon_count ; i++)
        {
          double dist_x, dist_y;
          pfm_geo_distance (pfm_handle[0], open_args[0].head.mbr.min_y, options.ex_polygon_x[i], options.ex_polygon_y[i],
                            options.ex_polygon_x[i], &dist_y);
          pfm_geo_distance (pfm_handle[0], options.ex_polygon_y[i], open_args[0].head.mbr.min_x, options.ex_polygon_y[i],
                            options.ex_polygon_x[i], &dist_x);

          options.ex_polygon_y[i] = dist_y;
          options.ex_polygon_x[i] = dist_x;
        }
    }


  //  Check for an inclusion area file.

  options.in_polygon_count = 0;
  if (!area_file.isEmpty ())
    {
      char af[512];
      strcpy (af, area_file.toLatin1 ());

      get_area_mbr (af, &options.in_polygon_count, options.in_polygon_x, options.in_polygon_y, &options.in_mbr);


      //  Convert the polygon to the pseudo X/Y that we will be using in the filter threads (we don't have to worry about the MBR
      //  because we don't use it).

      for (int32_t i = 0 ; i < options.in_polygon_count ; i++)
        {
          double dist_x, dist_y;
          pfm_geo_distance (pfm_handle[0], open_args[0].head.mbr.min_y, options.in_polygon_x[i], options.in_polygon_y[i],
                            options.in_polygon_x[i], &dist_y);
          pfm_geo_distance (pfm_handle[0], options.in_polygon_y[i], open_args[0].head.mbr.min_x, options.in_polygon_y[i],
                            options.in_polygon_x[i], &dist_x);

          options.in_polygon_y[i] = dist_y;
          options.in_polygon_x[i] = dist_x;
        }
    }


  overlap = NINT (options.hpRadius[2] / open_args[0].head.bin_size_xy) + 1;


  //  We're starting all FILTER_THREADS filter passes concurrently using threads.  Note that we're using the Qt::DirectConnection type
  //  for the signal/slot connections.  This causes all of the signals emitted from the threads to be serviced immediately.

  qRegisterMetaType<int32_t> ("int32_t");

  complete = NVFalse;
  for (int32_t i = 0 ; i < FILTER_THREADS ; i++)
    {
      options.filter_count[i] = options.point_count[i] = 0;
      pass_complete[i] = NVFalse;
      connect (&filter_thread[i], SIGNAL (percentValue (int32_t, int32_t)), this, SLOT (slotPercentValue (int32_t, int32_t)),
               Qt::DirectConnection);
      connect (&filter_thread[i], SIGNAL (completed (int32_t)), this, SLOT (slotCompleted (int32_t)), Qt::DirectConnection);
    }


  for (int32_t i = 0 ; i < FILTER_THREADS ; i++)
    {
      filter_thread[i].filter (&options, pfm_handle[i], &open_args[i], start_row[i], end_row[i], overlap, i);
    }


  //  We can't exit from this method until the threads are complete but we want to keep our progress bar updated.  This is a bit tricky 
  //  because you can't update the progress bar from within the slots connected to the thread signals.  Those slots are considered part
  //  of the filterion thread and not part of the GUI thread.  In the percent slot we just update the minimum percentage value (from
  //  any of the four threads) and monitor it here every second (updating the progress bar accordingly).  When all of the threads are
  //  finished we move on.

  while (!complete)
    {
#ifdef NVWIN3X
      Sleep (1000);
#else
      sleep (1);
#endif

      if (min_percent != old_percent)
        {
          progress.sbar->setValue (min_percent);
          old_percent = min_percent;
        }

      qApp->processEvents ();
    }


  progress.sbar->setValue (100);
  qApp->processEvents ();


  for (int32_t i = 0 ; i < FILTER_THREADS ; i++) close_pfm_file (pfm_handle[i]);


  progress.sbar->setRange (0, 100);
  progress.sbar->setValue (100);
  qApp->processEvents ();


  button (QWizard::FinishButton)->setEnabled (true);
  button (QWizard::CancelButton)->setEnabled (false);


  QApplication::restoreOverrideCursor ();


  progress.list->addItem (" ");

  int32_t filter_count = 0;
  int32_t point_count = 0;
  for (int32_t i = 0 ; i < FILTER_THREADS ; i++)
    {
      filter_count += options.filter_count[i];
      point_count += options.point_count[i];
    }
  float percent = ((float) filter_count / (float) point_count) * 100.0;

  if (options.invalidate)
    {
      qstring.sprintf (tr ("Filtering complete, %d of %d points (%0.2f%%) invalidated, press Finish to exit.").toLatin1 (), filter_count,
                      point_count, percent);
    }
  else
    {
      qstring.sprintf (tr ("Filtering complete, %d of %d points (%0.2f%%) marked suspect, press Finish to exit.").toLatin1 (), filter_count,
                      point_count, percent);
    }

  QListWidgetItem *cur = new QListWidgetItem (qstring);
  progress.list->addItem (cur);
  progress.list->setCurrentItem (cur);
  progress.list->scrollToItem (cur);



  char string[1024];
  FILE *hfp = fopen (open_args[0].list_path, "r+");
  if (fgets (string, sizeof (string), hfp) == NULL)
    {
      strcpy (string, tr ("Error reading the handle file %1 in file %2, function %3, line %4.  This shouldn't happen!\n").arg 
              (open_args[0].list_path).arg (__FILE__).arg (__FUNCTION__).arg (__LINE__).toUtf8 ());
      fprintf (stderr, "%s", string);
      exit (-1);
    }

  if (!strstr (string, "PFM Handle File"))
    {
      strcpy (string, tr ("Error reading the handle file %1 in file %2, function %3, line %4.  This shouldn't happen!\n").arg 
              (open_args[0].list_path).arg (__FILE__).arg (__FUNCTION__).arg (__LINE__).toUtf8 ());
      fprintf (stderr, "%s", string);
      exit (-1);
    }

  QString msg;

  if (options.invalidate)
    {
      msg = tr ("# --------------------------------------\n"
                "# CZMIL PFM Filter Statistics\n"
                "# --------------------------------------\n"
                "# Bathy[0] Density cutoff = %1\n"
                "# Bathy[0] Filter radius = %2\n"
                "# Bathy[0] Filter height = %3\n"
                "# Bathy[0] Required single line neighbors = %4\n"
                "# Bathy[0] Required multi-line neighbors = %5\n"
                "# Bathy[1] Density cutoff = %6\n"
                "# Bathy[1] Filter radius = %7\n"
                "# Bathy[1] Filter height = %8\n"
                "# Bathy[1] Required single line neighbors = %9\n"
                "# Bathy[1] Required multi-line neighbors = %10\n"
                "# Topo Filter radius = %11\n"
                "# Topo Filter height = %12\n"
                "# Topo Required single line neighbors = %13\n"
                "# Topo Required multi-line neighbors = %14\n"
                "# Total number of points processed %15\n"
                "# Number of soundings invalidated : %16\n"
                "# Percent of soundings invalidated : %17\n"
                "# --------------------------------------\n").arg
        (options.density[0]).arg (options.hpRadius[0]).arg (options.hpHeight[0]).arg (options.hpNeighbors[0]).arg
        (options.hpMultiNeighbors[0]).arg (options.density[1]).arg (options.hpRadius[1]).arg (options.hpHeight[1]).arg
        (options.hpNeighbors[1]).arg (options.hpMultiNeighbors[1]).arg (options.hpRadius[2]).arg (options.hpHeight[2]).arg
        (options.hpNeighbors[2]).arg (options.hpMultiNeighbors[2]).arg (point_count).arg (filter_count).arg (percent);
    }
  else
    {
      msg = tr ("# --------------------------------------\n"
                "# CZMIL PFM Filter Statistics\n"
                "# --------------------------------------\n"
                "# Bathy[0] Density cutoff = %1\n"
                "# Bathy[0] Filter radius = %2\n"
                "# Bathy[0] Filter height = %3\n"
                "# Bathy[0] Required single line neighbors = %4\n"
                "# Bathy[0] Required multi-line neighbors = %5\n"
                "# Bathy[1] Density cutoff = %6\n"
                "# Bathy[1] Filter radius = %7\n"
                "# Bathy[1] Filter height = %8\n"
                "# Bathy[1] Required single line neighbors = %9\n"
                "# Bathy[1] Required multi-line neighbors = %10\n"
                "# Topo Filter radius = %11\n"
                "# Topo Filter height = %12\n"
                "# Topo Required single line neighbors = %13\n"
                "# Topo Required multi-line neighbors = %14\n"
                "# Total number of points processed %15\n"
                "# Number of soundings marked suspect : %16\n"
                "# Percent of soundings suspect : %17\n"
                "# --------------------------------------\n").arg
        (options.density[0]).arg (options.hpRadius[0]).arg (options.hpHeight[0]).arg (options.hpNeighbors[0]).arg
        (options.hpMultiNeighbors[0]).arg (options.density[1]).arg (options.hpRadius[1]).arg (options.hpHeight[1]).arg
        (options.hpNeighbors[1]).arg (options.hpMultiNeighbors[1]).arg (options.hpRadius[2]).arg (options.hpHeight[2]).arg
        (options.hpNeighbors[2]).arg (options.hpMultiNeighbors[2]).arg (point_count).arg (filter_count).arg (percent);
    }

  strcpy (string, msg.toUtf8 ());

  fseek (hfp, 0, SEEK_END);
  fprintf (hfp, "%s", string);
  fclose (hfp);
}



void 
czmilPfmFilter::slotPercentValue (int32_t percent, int32_t pass)
{
  static int32_t save_percent[FILTER_THREADS];

  save_percent[pass] = percent;

  min_percent = 1001;
  for (int32_t i = 0 ; i < FILTER_THREADS ; i++) min_percent = qMin (min_percent, save_percent[i]);
}



void 
czmilPfmFilter::slotCompleted (int32_t pass)
{
  pass_complete[pass] = NVTrue;

  uint8_t done = NVTrue;
  for (int32_t i = 0 ; i < FILTER_THREADS ; i++) if (!pass_complete[i]) done = NVFalse;


  if (done) complete = NVTrue;
}



//  Get the users defaults.

void czmilPfmFilter::envin (OPTIONS *options)
{
  //  We need to get the font from the global settings.

#ifdef NVWIN3X
  QString ini_file2 = QString (getenv ("USERPROFILE")) + "/ABE.config/" + "globalABE.ini";
#else
  QString ini_file2 = QString (getenv ("HOME")) + "/ABE.config/" + "globalABE.ini";
#endif

  options->font = QApplication::font ();

  QSettings settings2 (ini_file2, QSettings::IniFormat);
  settings2.beginGroup ("globalABE");


  QString defaultFont = options->font.toString ();
  QString fontString = settings2.value (QString ("ABE map GUI font"), defaultFont).toString ();
  options->font.fromString (fontString);


  settings2.endGroup ();


  double saved_version = 1.0;


  // Set defaults so that if keys don't exist the parameters are defined

  options->density[0] = 0.2;
  options->hpRadius[0] = 3.5;
  options->hpHeight[0] = 0.7;
  options->hpNeighbors[0] = 2;
  options->hpMultiNeighbors[0] = 2;

  options->density[1] = 1.5;
  options->hpRadius[1] = 2.2;
  options->hpHeight[1] = 0.5;
  options->hpNeighbors[1] = 2;
  options->hpMultiNeighbors[1] = 2;

  options->hpRadius[2] = 8.0;
  options->hpHeight[2] = 8.0;
  options->hpNeighbors[2] = 2;
  options->hpMultiNeighbors[2] = 2;

  options->invalidate = NVFalse;

  options->input_dir = ".";
  options->area_dir = ".";
  options->exclude_dir = ".";
  options->window_x = 0;
  options->window_y = 0;
  options->window_width = 640;
  options->window_height = 200;


  //  Get the INI file name

#ifdef NVWIN3X
  QString ini_file = QString (getenv ("USERPROFILE")) + "/ABE.config/czmilPfmFilter.ini";
#else
  QString ini_file = QString (getenv ("HOME")) + "/ABE.config/czmilPfmFilter.ini";
#endif

  QSettings settings (ini_file, QSettings::IniFormat);
  settings.beginGroup ("czmilPfmFilter");

  saved_version = settings.value (QString ("settings version"), saved_version).toDouble ();


  //  If the settings version has changed we need to leave the values at the new defaults since they may have changed.

  if (settings_version != saved_version) return;


  for (int32_t i = 0 ; i < 3 ; i++)
    {
      if (i < 2) options->density[i] = settings.value (QString ("Density [%1]").arg (i), options->density[i]).toDouble ();

      options->hpRadius[i] = settings.value (QString ("HP Radius [%1]").arg (i), options->hpRadius[i]).toDouble ();
      options->hpHeight[i] = settings.value (QString ("HP Height [%1]").arg (i), options->hpHeight[i]).toDouble ();
      options->hpNeighbors[i] = settings.value (QString ("HP Single Line Neighbors [%1]").arg (i), options->hpNeighbors[i]).toInt ();
      options->hpMultiNeighbors[i] = settings.value (QString ("HP Multi-Line Neighbors"), options->hpMultiNeighbors[i]).toInt ();
    }

  options->invalidate = settings.value (QString ("Invalidate flag"), options->invalidate).toBool ();

  options->input_dir = settings.value (QString ("input directory"), options->input_dir).toString ();
  options->area_dir = settings.value (QString ("area directory"), options->area_dir).toString ();
  options->exclude_dir = settings.value (QString ("exclude directory"), options->exclude_dir).toString ();

  options->window_width = settings.value (QString ("width"), options->window_width).toInt ();
  options->window_height = settings.value (QString ("height"), options->window_height).toInt ();
  options->window_x = settings.value (QString ("x position"), options->window_x).toInt ();
  options->window_y = settings.value (QString ("y position"), options->window_y).toInt ();

  settings.endGroup ();
}




//  Save the users defaults.

void czmilPfmFilter::envout (OPTIONS *options)
{
  //  Get the INI file name

#ifdef NVWIN3X
  QString ini_file = QString (getenv ("USERPROFILE")) + "/ABE.config/czmilPfmFilter.ini";
#else
  QString ini_file = QString (getenv ("HOME")) + "/ABE.config/czmilPfmFilter.ini";
#endif

  QSettings settings (ini_file, QSettings::IniFormat);
  settings.beginGroup ("czmilPfmFilter");


  settings.setValue (QString ("settings version"), settings_version);

  for (int32_t i = 0 ; i < 3 ; i++)
    {
      if (i < 2) settings.setValue (QString ("Density [%1]").arg (i), options->density[i]);

      settings.setValue (QString ("HP Radius [%1]").arg (i), options->hpRadius[i]);
      settings.setValue (QString ("HP Height [%1]").arg (i), options->hpHeight[i]);
      settings.setValue (QString ("HP Single Line Neighbors [%1]").arg (i), options->hpNeighbors[i]);
      settings.setValue (QString ("HP Multi-Line Neighbors"), options->hpMultiNeighbors[i]);
    }

  settings.setValue (QString ("Invalidate flag"), options->invalidate);

  settings.setValue (QString ("input directory"), options->input_dir);
  settings.setValue (QString ("area directory"), options->area_dir);
  settings.setValue (QString ("exclude directory"), options->exclude_dir);

  settings.setValue (QString ("width"), options->window_width);
  settings.setValue (QString ("height"), options->window_height);
  settings.setValue (QString ("x position"), options->window_x);
  settings.setValue (QString ("y position"), options->window_y);

  settings.endGroup ();
}
