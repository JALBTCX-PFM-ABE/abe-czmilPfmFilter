
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



QString densityText0 = 
  optionPage::tr ("Change minimum bathymetric data (classifications 40 and 42) data density.  If the bathy points are less dense than "
                  "this value, the data will not be filtered.  Bathy data with densities between this value and the second level "
                  "bathy density will be filtered using the first level filter.");

QString hpRadiusValueText0 = 
  optionPage::tr ("Change the X/Y <b>Radius</b> (in meters) to be used for the first level bathy Hockey Puck filter.  "
                  "Increasing this value will decrease the amount of filtering.<br><br>"
                  "<b>IMPORTANT NOTE: The horizontal uncertainty of each of the two points being compared at any given time is added to the "
                  "horizontal radius so that any possible overlap of the positional data can be used to validate a point.</b>");

QString hpHeightValueText0 = 
  optionPage::tr ("Change the vertical <b>Height</b> (in meters) to be used for the first level bathy Hockey Puck filter.  "
                  "Increasing this value will decrease the amount of filtering.");

QString hpNeighborsValueText0 = 
  optionPage::tr ("Change the number of <b>Neighbors</b> required within the horizontal <b>Radius</b> and vertical <b>Height</b> "
                  "(i.e. the hockey puck) of the Hockey Puck filter for the first level bathy filter.  Increasing this value will "
                  "increase the amount of filtering.  Setting this value to 0 will force the filter to only consider points in "
                  "areas with multiple lines (safer).");

QString hpMultiNeighborsValueText0 = 
  optionPage::tr ("Change the number of <b>Multi-line Neighbors</b> (i.e. neighbors when more than one line is present) required within the "
                  "horizontal <b>Radius</b> and vertical <b>Height</b> (i.e. the hockey puck) of the Hockey Puck filter for the first "
                  "level bathy filter.  Increasing this value will increase the amount of filtering.");

QString densityText1 = 
  optionPage::tr ("Change bathymetric data (classifications 40 and 42) data density cutoff.  If the bathy points are at least this dense "
                  "they will be filtered using this second level filter.");

QString hpRadiusValueText1 = 
  optionPage::tr ("Change the X/Y <b>Radius</b> (in meters) to be used for the second level bathy Hockey Puck filter.  "
                  "Increasing this value will decrease the amount of filtering.<br><br>"
                  "<b>IMPORTANT NOTE: The horizontal uncertainty of each of the two points being compared at any given time is added to the "
                  "horizontal radius so that any possible overlap of the positional data can be used to validate a point.</b>");

QString hpHeightValueText1 = 
  optionPage::tr ("Change the vertical <b>Height</b> (in meters) to be used for the second level bathy Hockey Puck filter.  "
                  "Increasing this value will decrease the amount of filtering.");

QString hpNeighborsValueText1 = 
  optionPage::tr ("Change the number of <b>Neighbors</b> required within the horizontal <b>Radius</b> and vertical <b>Height</b> "
                  "(i.e. the hockey puck) of the Hockey Puck filter for the second level bathy filter.  Increasing this value will "
                  "increase the amount of filtering.  Setting this value to 0 will force the filter to only consider points in "
                  "areas with multiple lines (safer).");

QString hpMultiNeighborsValueText1 = 
  optionPage::tr ("Change the number of <b>Multi-line Neighbors</b> (i.e. neighbors when more than one line is present) required within the "
                  "horizontal <b>Radius</b> and vertical <b>Height</b> (i.e. the hockey puck) of the Hockey Puck filter for the second "
                  "level bathy filter.  Increasing this value will increase the amount of filtering.");

QString hpRadiusValueText2 = 
  optionPage::tr ("Change the X/Y <b>Radius</b> (in meters) to be used for the topo Hockey Puck filter.  "
                  "Increasing this value will decrease the amount of filtering.<br><br>"
                  "<b>IMPORTANT NOTE: The horizontal uncertainty of each of the two points being compared at any given time is added to the "
                  "horizontal radius so that any possible overlap of the positional data can be used to validate a point.</b>");

QString hpHeightValueText2 = 
  optionPage::tr ("Change the vertical <b>Height</b> (in meters) to be used for the topo Hockey Puck filter.  "
                  "Increasing this value will decrease the amount of filtering.");

QString hpNeighborsValueText2 = 
  optionPage::tr ("Change the number of <b>Neighbors</b> required within the horizontal <b>Radius</b> and vertical <b>Height</b> "
                  "(i.e. the hockey puck) of the Hockey Puck filter for the topo filter.  Increasing this value will "
                  "increase the amount of filtering.  Setting this value to 0 will force the filter to only consider points in "
                  "areas with multiple lines (safer).");

QString hpMultiNeighborsValueText2 = 
  optionPage::tr ("Change the number of <b>Multi-line Neighbors</b> (i.e. neighbors when more than one line is present) required within the "
                  "horizontal <b>Radius</b> and vertical <b>Height</b> (i.e. the hockey puck) of the Hockey Puck filter for the topo "
                  "filter.  Increasing this value will increase the amount of filtering.");

QString invText = 
  optionPage::tr ("Check this box if you wish to mark filtered data points as PFM_FILTER_INVAL instead of PFM_SUSPECT.<br><br>"
                  "<b>WARNING: This should only be done if you are absolutely sure that you will not be filtering out real, "
                  "hydrographic data!  This option should probably only be used for topographic LiDAR data.</b>");
