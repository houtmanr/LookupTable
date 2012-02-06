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

void Sclass::processSuccession(vector<Sclass> treeList, vector<Sclass> tableValues){

  
  int size_class;
  int density_class;
  int succession_class;
  int j = 0; // Tracks years.

  int sizeTL = treeList.size();
  int i = 0; // Tracks trees.
  while(i<(sizeTL-1))
  {
    int year_count = treeList.at(i).year;
    int treeCn_count = treeList.at(i).treeCn;
      
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

	char ponderosa[9];
	char lodgepole[9];
	strcpy_s(ponderosa, "PP      ");
	strcpy_s(lodgepole, "LP      ");

    while(treeList.at(i).year == year_count)
	{
      if(strcmp(treeList.at(i).species, ponderosa) == 0)
      {
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
      else if(strcmp(treeList.at(i).species, lodgepole) == 0)
      {	
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
      else if(strcmp(treeList.at(i).species, lodgepole) != 0 && strcmp(treeList.at(i).species, ponderosa) != 0)
      {	
        while(strcmp(treeList.at(i).species, lodgepole) != 0 && strcmp(treeList.at(i).species, ponderosa) != 0 && treeList.at(i).year == year_count)
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
      succession_class = 1; // A
    }
    else if(size_class == 2 && density_class == 1)
    {
      succession_class = 3; // C
    }
    else if(size_class == 2 && density_class == 2)
    {
      succession_class = 2; // B
    }
    else if(size_class == 3 && density_class == 1)
    {
      succession_class = 4; // D
    }
    else
    {
      succession_class = 5; // E
    }

	}
   
    tableValues.at(j).successionClass = succession_class;
	j++;
  }
  
  createLookupTable(tableValues);
  
};

void Sclass::createLookupTable(vector<Sclass> tableValues)
{
	FILE *fout;
	int canopy_cover, crown_base_height, canopy_height, crown_bulk_density;

	fout = fopen("..\\..\\FVSOutputFiles\\Ponderosa_Fire_A_B_C_D_E_Output.txt","a");

	canopy_cover = 0;
	crown_base_height = 0;
	canopy_height = 0;
	crown_bulk_density = 0;
	
	int i = 0;
	int sclass_count = tableValues[i].successionClass;
	int year_count = tableValues[i].year;
	int fuel_model = tableValues[i].fml;
	double sdi_count = tableValues[i].sdi;
	double ba_count = tableValues[i].ba;
	double tpa_count = tableValues[i].tpa;
	double bdft_count = tableValues[i].bdft;


	fprintf(fout, "stand_id year sclass canopy_cover crown_base_height canopy_height crown_bulk_density fuel_model stand_density_index basal_area trees_per_acre removed_bdft\n");


	int j = tableValues.size();
	while ( i < j )
	{
		int sclass_count = tableValues[i].successionClass;
		int fuel_model = tableValues[i].fml;
		int year_count = tableValues[i].year;
		double sdi_count = tableValues[i].sdi;
	    double ba_count = tableValues[i].ba;
	    double tpa_count = tableValues[i].tpa;
	    double bdft_count = tableValues[i].bdft;
		treeCn = tableValues[i].treeCn;

				if(tableValues[i].cover > 0 && tableValues[i].cover < 1)
				{
					canopy_cover = 0;
				}
				else if(tableValues[i].cover >= 1 && tableValues[i].cover < 25)
				{
					canopy_cover = 20;
				}
				else if(tableValues[i].cover >= 25 && tableValues[i].cover < 50)
				{
					canopy_cover = 45;
				}
				else if(tableValues[i].cover >= 50 && tableValues[i].cover < 75)
				{
					canopy_cover = 70;
				}
				else
				{
					canopy_cover = 95;
				}

				if(tableValues[i].heightLive > 0 && tableValues[i].heightLive < 1)
				{
					crown_base_height = 0;
				}
				else if(tableValues[i].heightLive >= 1 && tableValues[i].heightLive < 10)
				{
					crown_base_height = 50;
				}
				else if(tableValues[i].heightLive >= 10 && tableValues[i].heightLive < 20)
				{
					crown_base_height = 150;
				}
				else if(tableValues[i].heightLive >= 20 && tableValues[i].heightLive < 30)
				{
					crown_base_height = 250;
				}
				else
				{
					crown_base_height = 350;
				}
				
				if(tableValues[i].height > 0 && tableValues[i].height < 1)
				{
					canopy_height = 0;
				}
				else if(tableValues[i].height >= 1 && tableValues[i].height < 30)
				{
					canopy_height = 150;
				}
				else if(tableValues[i].height >= 30 && tableValues[i].height < 60)
				{
					canopy_height = 450;
				}
				else if(tableValues[i].height >= 60 && tableValues[i].height < 90)
				{
					canopy_height = 750;
				}
				else if(tableValues[i].height >= 90)
				{
					canopy_height = 1000;
				}
				
				if(tableValues[i].cbd > 0 && tableValues[i].cbd < .01)
				{
					crown_bulk_density = 0;
				}
				else if(tableValues[i].cbd >= .01 && tableValues[i].cbd < .06)
				{
					crown_bulk_density = 3;
				}
				else if(tableValues[i].cbd >= .06 && tableValues[i].cbd < .1)
				{
					crown_bulk_density = 8;
				}
				else if(tableValues[i].cbd >= .1 && tableValues[i].cbd < .2)
				{
					crown_bulk_density = 15;
				}
				else if(tableValues[i].cbd >= .02)
				{
					crown_bulk_density = 28;
				}
				i++;
		
				fprintf(fout, "%d %d %d %d %d %d %d %d %lf %lf %lf %lf\n", 
					treeCn, year_count, sclass_count, canopy_cover, crown_base_height, canopy_height, crown_bulk_density, fuel_model, sdi_count, ba_count, tpa_count, bdft_count);
	}
	fclose(fout);

};

Sclass::Sclass(int pTreeCn, int pYear, double pCover, int pFml, double pHeight, double pHeightLive, double pCbd, double psdi, double pba, double ptpa, double pbdft){
  treeCn = pTreeCn;
  fml = pFml;
  cover = pCover;
  height = pHeight;
  heightLive = pHeightLive;
  cbd = pCbd;
  year = pYear;
  sdi = psdi;
  ba = pba;
  tpa = ptpa;
  bdft = pbdft;
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