// Ponderosa_Lookup_Table.cpp : Defines the entry point for the console application.
//
#include "stdio.h"
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <assert.h>
#include <math.h>
#include "Sclass.h"
#include "CreateLookupTable.h"

typedef struct
{
int stand_id;
int sclass;
int year;
int canopy;
int fml;
double htt;
int htlive;
double cbd;
}plot;

LUTable::LUTable(int lookuptable)
{
	FILE *ponderosa;
	FILE *fout;
	char header[256];
	int i;
	int j;
	int k;
	plot plots[650];
	int canopy_cover, crown_base_height, canopy_height, crown_bulk_density;

	ponderosa = fopen("N:\\Visual_Basic\\Ponderosa_Fire_A_B_C_D_E.txt","r");
	fout = fopen("N:\\Visual_Basic\\Ponderosa_Fire_A_B_C_D_E_Output.txt","w");

	fgets(header,sizeof(header), ponderosa);

	i = 0;
	j = 0;// Counts the number of stands

	while(!feof(ponderosa))
	{
		fscanf(ponderosa, "%d %d %d %d %lf %d %lf %d\n", &plots[i].stand_id, &plots[i].sclass, &plots[i].year, &plots[i].canopy, &plots[i].htt, &plots[i].htlive, &plots[i].cbd, &plots[i].fml);
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

	fprintf(fout, "stand_id sclass year canopy_cover crown_base_height canopy_height crown_bulk_density fuel_model\n");

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
		
				fprintf(fout, "%d %d %d %d %d %d %d %d\n", 
					stand_id_count, sclass_count, year_count, canopy_cover, crown_base_height, canopy_height, crown_bulk_density, fuel_model);
			}
		}
		
	k++;
	}


}