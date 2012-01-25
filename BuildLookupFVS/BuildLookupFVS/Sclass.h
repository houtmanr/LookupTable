#include <vector>

using std::vector;

class Sclass{
public:
  ~Sclass(void);
  Sclass();
  Sclass(int pTreeCn, int pyear, int pFml, double pHeight, double pHeightLive, double pCbd);
  void processSuccession(vector<Sclass> charicteristic);
  

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
