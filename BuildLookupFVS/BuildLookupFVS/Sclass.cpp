// Labels each stand by succession class
//

#include "stdio.h"
#include "stdafx.h"
#include <math.h>
#include <vector>
#include "Sclass.h"

using std::vector;

Sclass::Sclass(){
	
};

void Sclass::processSuccession(vector<Sclass> treeList){

  
  int size_class;
  int density_class;
  char succession_class[2];

  double total1 = 0;
  double total2 = 0;
  double total3 = 0;
  double pp_tpa21 = 0;
  double lp_tpa21 = 0;
  double other_tpa21 = 0;
  double pp_cover21 = 0;
  double lp_cover21 = 0;
  double other_cover21 = 0;
  double pp_cover5to21 = 0;
  double lp_cover5to21 = 0;
  double other_cover5to21 = 0;
  double pp_cover0to5 = 0;
  double lp_cover0to5 = 0;
  double other_cover0to5 = 0;

  int size = treeList.size();

  int i = 0;
  while(i<size)
  {
    int year_count = treeList.at(i).year;
    int treeCn_count = treeList.at(i).treeCn;
      
	pp_tpa21 = 0;
    pp_cover21 = 0;
    pp_cover5to21 = 0;
    pp_cover0to5 = 0;

	char * ponderosa("PP");
	char * lodgepole("LP");

    while(treeList.at(i).year == year_count)
	{
      if(strcmp(treeList.at(i).species, ponderosa) == 0)
      {
        total1 = 0;

        while(strcmp(treeList.at(i).species, ponderosa) == 0 && treeList.at(i).year == year_count)
        {
          total1 = total1 + treeList.at(i).cover;

          if(treeList.at(i).dbh >= 21)
          {
            pp_tpa21 = pp_tpa21 + treeList.at(i).treeCount;
            pp_cover21 = pp_cover21 + treeList.at(i).cover;
          }

          else if(treeList.at(i).dbh >= 5 && treeList.at(i).dbh < 21)
          {
            pp_cover5to21 = pp_cover5to21 + treeList.at(i).cover;
          }

          else
          {
            pp_cover0to5 = pp_cover0to5 + treeList.at(i).cover;
          }
		  i++;
        }
				
      }
      else
      {
        total1 = 0;
      }

      lp_tpa21 = 0;
      lp_cover21 = 0;
      lp_cover5to21 = 0;
      lp_cover0to5 = 0;

      if(strcmp(treeList.at(i).species, lodgepole) == 0)
      {
        total2 = 0;
				
        while(strcmp(treeList.at(i).species, lodgepole) == 0 && treeList.at(i).year == year_count)
        {
          total2 = total2 + treeList.at(i).cover;

          if(treeList.at(i).dbh >= 21)
          {
            lp_tpa21 = lp_tpa21 + treeList.at(i).treeCount;
            lp_cover21 = lp_cover21 + treeList.at(i).cover;
          }
          else if(treeList.at(i).dbh >= 5 && treeList.at(i).dbh < 21)
          {
            lp_cover5to21 = lp_cover5to21 + treeList.at(i).cover;
          }
          else
          {
          lp_cover0to5 = lp_cover0to5 + treeList.at(i).cover;
          }
		  i++;
        }
      }
      else
      {
        total2 = 0;
      }

      other_tpa21 = 0;
      other_cover21 = 0;
      other_cover5to21 = 0;
      other_cover0to5 = 0;


      if(strcmp(treeList.at(i).species, lodgepole) == 1 && strcmp(treeList.at(i).species, ponderosa) == 1)
      {
        total3 = 0;
				
        while(strcmp(treeList.at(i).species, lodgepole) == 1 && strcmp(treeList.at(i).species, ponderosa) == 1 && treeList.at(i).year == year_count)
        {
          total3 = total3 + treeList.at(i).cover;

          if(treeList.at(i).dbh >= 21)
          {
            other_tpa21 = other_tpa21 + treeList.at(i).treeCount;
            other_cover21 = other_cover21 + treeList.at(i).cover;
          }
          else if(treeList.at(i).dbh >= 5 && treeList.at(i).dbh < 21)
          {
            other_cover5to21 = other_cover5to21 + treeList.at(i).cover;
          }
          else
          {
            other_cover0to5 = other_cover0to5 + treeList.at(i).cover;
          }
		  i++;
        }
      }
      else
      {
        total3 = 0;
      }
      
   }

    double total = total1 + total2 + total3;
    double total_percent_cover = 100*(1-exp(-.01*total));
    double percent_ponderosa = 100*(1-exp(-.01*total1));
    double percent_lodgepole = 100*(1-exp(-.01*total2));
    double percent_other = 100*(1-exp(-.01*total3));
    double total_tpa21 = pp_tpa21 + lp_tpa21 + other_tpa21;
    double total_cover21 = pp_cover21 + lp_cover21 + other_cover21;
    double total_cover21_percent = 100*(1-exp(-.01*total_cover21));
    double total_cover5to21 = pp_cover5to21 + lp_cover5to21 + other_cover5to21;
    double total_cover5to21_percent = 100*(1-exp(-.01*total_cover5to21));
    double total_cover0to5 = pp_cover0to5 + lp_cover0to5 + other_cover0to5;
    double total_cover0to5_percent = 100*(1-exp(-.01*total_cover0to5));

	for(int l = 0; l < i; l++)
	{
    if(total_percent_cover < 10)
    {
      size_class = 1;
    } 
    else if(total_tpa21 >= 10)
    {
      size_class = 3;
    }
    else if(total_cover21_percent >= 50)
    {
      size_class = 3;
    }
    else if(total_cover5to21_percent >= 50)
    {
      size_class = 2;
    }
    else if(total_cover21_percent + total_cover5to21_percent >= 20 || total_cover21_percent + total_cover5to21_percent > total_cover0to5)
    {
      size_class = 2;
    }
    else if(total_cover0to5_percent >= 50 || total_cover0to5_percent > total_cover21_percent + total_cover5to21_percent)
    {
      size_class = 1;
    }
    else if(total_cover21_percent >= total_cover5to21_percent && total_cover21_percent > total_cover0to5_percent)
    {
      size_class = 3;
    }
    else if(total_cover5to21_percent >= total_cover21_percent && total_cover5to21_percent > total_cover0to5_percent)
    {
      size_class = 2;
    }
    else
    {
      size_class = 1;
    }

    if(total_percent_cover <= 40)
    {
      density_class = 1;
    }
    else
    {
      density_class = 2;
    }

    if(size_class == 1)
    {
      sprintf_s(succession_class,"A"); // Can I just put a in place of "A"?  Same for the rest of the classes..."B"=2, "C"=3...
    }
    else if(size_class == 2 && density_class == 1)
    {
      sprintf_s(succession_class,"C");
    }
    else if(size_class == 2 && density_class == 2)
    {
      sprintf_s(succession_class,"B");
    }
    else if(size_class == 3 && density_class == 1)
    {
      sprintf_s(succession_class,"D");
    }
    else
    {
      sprintf_s(succession_class,"E");
    }

	}
   
   treeList.at(i).treeCn, treeList.at(i).year, succession_class;
  }
	
};

Sclass::Sclass(int pTreeCn, int pYear, int pFml, double pHeight, double pHeightLive, double pCbd){
  treeCn = pTreeCn;
  fml = pFml;
  height = pHeight;
  heightLive = pHeightLive;
  cbd = pCbd;
  year = pYear;
};

 
Sclass::Sclass(int pTreeCn, int pYear, double pTreeCount, char pSpecies[2], double pDbh, double pCover){
	treeCn = pTreeCn;
	year = pYear;
	treeCount = pTreeCount;
	dbh = pDbh;
	cover = pCover;
	strcpy(species, pSpecies);

};


Sclass::~Sclass(){
};