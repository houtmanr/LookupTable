// Labels each stand by succession class
//

#include "stdio.h"
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <assert.h>
#include <math.h>
#include <vector>
#include "Sclass.h"

using std::vector;

Sclass::Sclass(){
	
};

void Sclass::processSuccession(vector<Sclass> charicteristics){

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

  int k = 0;
  int j = 0;
  int i = 0;
  while(k<=j)
  {
    int year_count = charicteristics.at(i).year;
    int treeCn_count = charicteristics.at(i).treeCn;

    while(charicteristics.at(i).year == year_count)
    {
      pp_tpa21 = 0;
      pp_cover21 = 0;
      pp_cover5to21 = 0;
      pp_cover0to5 = 0;

      if(charicteristics.at(i).species == 1)
      {
        total1 = 0;

        while(charicteristics.at(i).species == 1 && charicteristics.at(i).year == year_count)
        {
          total1 = total1 + charicteristics.at(i).cover;

          if(charicteristics.at(i).dbh >= 21)
          {
            pp_tpa21 = pp_tpa21 + charicteristics.at(i).treeCount;
            pp_cover21 = pp_cover21 + charicteristics.at(i).cover;
          }

          else if(charicteristics.at(i).dbh >= 5 && charicteristics.at(i).dbh < 21)
          {
            pp_cover5to21 = pp_cover5to21 + charicteristics.at(i).cover;
          }

          else
          {
            pp_cover0to5 = pp_cover0to5 + charicteristics.at(i).cover;
          }

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

      if(charicteristics.at(i).species == 2)
      {
        total2 = 0;
				
        while(charicteristics.at(i).species == 2 && charicteristics.at(i).year == year_count)
        {
          total2 = total2 + charicteristics.at(i).cover;

          if(charicteristics.at(i).dbh >= 21)
          {
            lp_tpa21 = lp_tpa21 + charicteristics.at(i).treeCount;
            lp_cover21 = lp_cover21 + charicteristics.at(i).cover;
          }
          else if(charicteristics.at(i).dbh >= 5 && charicteristics.at(i).dbh < 21)
          {
            lp_cover5to21 = lp_cover5to21 + charicteristics.at(i).cover;
          }
          else
          {
          lp_cover0to5 = lp_cover0to5 + charicteristics.at(i).cover;
          }
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


      if(charicteristics.at(i).species > 2)
      {
        total3 = 0;
				
        while(charicteristics.at(i).species > 2 && charicteristics.at(i).year == year_count)
        {
          total3 = total3 + charicteristics.at(i).cover;

          if(charicteristics.at(i).dbh >= 21)
          {
            other_tpa21 = other_tpa21 + charicteristics.at(i).treeCount;
            other_cover21 = other_cover21 + charicteristics.at(i).cover;
          }
          else if(charicteristics.at(i).dbh >= 5 && charicteristics.at(i).dbh < 21)
          {
            other_cover5to21 = other_cover5to21 + charicteristics.at(i).cover;
          }
          else
          {
            other_cover0to5 = other_cover0to5 + charicteristics.at(i).cover;
          }
        }
      }
      else
      {
        total3 = 0;
      }
      k++;
	  i++;
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

   
      treeCn_count, year_count, total1, total2, total3, total, 
      total_percent_cover, percent_ponderosa, percent_lodgepole, percent_other, 
      pp_tpa21, lp_tpa21, other_tpa21, total_tpa21,
      pp_cover21, lp_cover21, other_cover21, total_cover21, total_cover21_percent,
      pp_cover5to21, lp_cover5to21, other_cover5to21, total_cover5to21, total_cover5to21_percent,
      pp_cover0to5, lp_cover0to5, other_cover0to5, total_cover0to5, total_cover0to5_percent,
      size_class, density_class, succession_class;
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

Sclass::~Sclass(){
};