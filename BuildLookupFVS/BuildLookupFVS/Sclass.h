#include <vector>

using std::vector;

class Sclass{
public:
  ~Sclass(void);
  Sclass();
  Sclass(int pTreeCn, int pYear, double pCover, int pFml, double pHeight, double pHeightLive, double pCbd);
  Sclass(int pTreeCn, int pYear, double pTreeValue, char pSpecies[3], double pDbh, double pCrownWidth);
  void createLookupTable(vector<Sclass> tableValues);
  void processSuccession(vector<Sclass> treeList, vector<Sclass> tableValues);

private:
  // Set these values from the output of FVS.
  int treeCn;//StandID
  int year;	
  int fml;
  int successionClass;
  double cbd;
  double height;
  double heightLive;
  char species[8];
  double treeVolume;
  double treeCount;  // Trees per acre (TPA)
  double dbh;
  double baAcre;     // ba_acre = .005454 * tree_count * dbh^2
  double crownWidth; // Need crown_width in order to compute cover
  double cover;
};
