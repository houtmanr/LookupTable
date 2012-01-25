#include <afxdb.h>



class DBase
{
public:
  DBase();
  void Charicteristics(int standId);
  int getYear();
  ~DBase(void);
private:
	  // Set these values from the output of FVS.
  int treeCn;//StandID
  int year;	
  int fml;
  int species;
  int successionClass;
  double cbd;
  double height;
  double heightLive;
  double treeVolume;
  double treeCount;  //Trees per acre (TPA)
  double dbh;
  double baAcre;     // ba_acre = .005454 * tree_count * dbh^2
  double crownWidth; // Need crown_width in order to compute cover
  double cover;
};