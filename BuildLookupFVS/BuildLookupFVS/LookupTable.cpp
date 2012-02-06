// Creates the necessary input for the Lookup Table
//


#include "stdio.h"
#include "stdafx.h"
#include <vector>
#include <math.h>
#include "LookupTable.h"

using std::vector;

LookupTable::LookupTable(){

};

void LookupTable::processLookupTable(vector<LookupTable compute){


    int stand_id;
    int sclass;
    int year;
    int canopy;
    int fml;
    double htt;
    int htlive;
    double cbd;
    double sdi;
    double ba;
    double tpa;
    double bdft;

	FILE *ponderosa;
	FILE *fout;
	char header[256];
	int i;
	int j;
	int k;
	plot plots[650];
	int canopy_cover, crown_base_height, canopy_height, crown_bulk_density;

	ponderosa = fopen("N:\\Five_Year_Simulations\\2873_Compute.txt","r");
	fout = fopen("N:\\Five_Year_Simulations\\2873_Compute_Output.txt","w");

	fgets(header,sizeof(header), ponderosa);

	i = 0;
	j = 0;// Counts the number of stands

	while(!feof(ponderosa))
	{
		fscanf(ponderosa, "%d %d %d %d %lf %d %lf %d %lf %lf %lf %lf\n", &plots[i].stand_id, &plots[i].sclass, &plots[i].year, &plots[i].canopy, &plots[i].htt, &plots[i].htlive, &plots[i].cbd, &plots[i].fml, &plots[i].sdi, &plots[i].ba, &plots[i].tpa, &plots[i].bdft);
		if(i>0 && plots[i].stand_id != plots[i-1].stand_id)
		{
			j++;
		}
		i++;
	}

	fclose(ponderosa);

	i = 0;
	k = 0;

	canopy_cover = 0;
	crown_base_height = 0;
	canopy_height = 0;
	crown_bulk_density = 0;
	
	int sclass_count = plots[i].sclass;
	int year_count = plots[i].year;
	int fuel_model = plots[i].fml;
	double sdi_count = plots[i].sdi;
	double ba_count = plots[i].ba;
	double tpa_count = plots[i].tpa;
	double bdft_count = plots[i].bdft;

	fprintf(fout, "stand_id sclass year canopy_cover crown_base_height canopy_height crown_bulk_density fuel_model stand_density_index basal_area trees_per_acre bdft\n");

	while(k<=j)
	{
		int stand_id_count = plots[i].stand_id;
		while(plots[i].stand_id == stand_id_count)
		{
			while (plots[i].stand_id == stand_id_count)
			{
				int sclass_count = plots[i].sclass;
				int fuel_model = plots[i].fml;
				int year_count = plots[i].year;
				double sdi_count = plots[i].sdi;
	            double ba_count = plots[i].ba;
	            double tpa_count = plots[i].tpa;
	            double bdft_count = plots[i].bdft;
				
				if(plots[i].canopy > 0 && plots[i].canopy < 1)
				{
					canopy_cover = 0;
				}
				else if(plots[i].canopy >= 1 && plots[i].canopy < 25)
				{
					canopy_cover = 20;
				}
				else if(plots[i].canopy >= 25 && plots[i].canopy < 50)
				{
					canopy_cover = 45;
				}
				else if(plots[i].canopy >= 50 && plots[i].canopy < 75)
				{
					canopy_cover = 70;
				}
				else
				{
					canopy_cover = 95;
				}

				if(plots[i].htlive > 0 && plots[i].htlive < 1)
				{
					crown_base_height = 0;
				}
				else if(plots[i].htlive >= 1 && plots[i].htlive < 10)
				{
					crown_base_height = 50;
				}
				else if(plots[i].htlive >= 10 && plots[i].htlive < 20)
				{
					crown_base_height = 150;
				}
				else if(plots[i].htlive >= 20 && plots[i].htlive < 30)
				{
					crown_base_height = 250;
				}
				else
				{
					crown_base_height = 350;
				}
				
				if(plots[i].htt > 0 && plots[i].htt < 1)
				{
					canopy_height = 0;
				}
				else if(plots[i].htt >= 1 && plots[i].htt < 30)
				{
					canopy_height = 150;
				}
				else if(plots[i].htt >= 30 && plots[i].htt < 60)
				{
					canopy_height = 450;
				}
				else if(plots[i].htt >= 60 && plots[i].htt < 90)
				{
					canopy_height = 750;
				}
				else if(plots[i].htt >= 90)
				{
					canopy_height = 1000;
				}
				
				if(plots[i].cbd > 0 && plots[i].cbd < .01)
				{
					crown_bulk_density = 0;
				}
				else if(plots[i].cbd >= .01 && plots[i].cbd < .06)
				{
					crown_bulk_density = 3;
				}
				else if(plots[i].cbd >= .06 && plots[i].cbd < .1)
				{
					crown_bulk_density = 8;
				}
				else if(plots[i].cbd >= .1 && plots[i].cbd < .2)
				{
					crown_bulk_density = 15;
				}
				else if(plots[i].cbd >= .02)
				{
					crown_bulk_density = 28;
				}
				i++;
		
				fprintf(fout, "%d %d %d %d %d %d %d %d %lf %lf %lf %lf\n", 
					stand_id_count, year_count, sclass_count, canopy_cover, crown_base_height, canopy_height, crown_bulk_density, fuel_model, sdi_count, ba_count, tpa_count, bdft_count);
			}
		}
		
	k++;
	}

	return 0;
}

