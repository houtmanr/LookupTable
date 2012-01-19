// Labels each stand by succession class
//

#include "stdio.h"
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <assert.h>
#include <math.h>
#include "Sclass.h"


typedef struct
{							//This data come from the FVS_TreeList.  below is what is required - but still need CrWidth in otder to make cover.
int tree_cn;				//StandID
int year;						
int species;
double tree_count;			//Trees per acre (TPA)
double dbh;
double ba_acre;				// ba_acre = .005454 * tree_count * dbh^2
//double crown_width		   need crown_width in order to compute cover
double cover;				// cover = 100 * (1 - exp(-.01 * crown_width^2 * tree_count * .001803))
}plot;

Sclass::Sclass(int sclass)
{
	FILE *ponderosa;		//These FILEs need to access to the DatabaseProcessing.cpp output
	FILE *fout;				//
	char header[256];
	int i;
	int j;
	int k;
	int l;
	plot plots[20000];
	double total1, total2, total3;
	double pp_tpa21, lp_tpa21, other_tpa21;
	double pp_cover21, lp_cover21, other_cover21;
	double pp_cover5to21, lp_cover5to21, other_cover5to21;
	double pp_cover0to5, lp_cover0to5, other_cover0to5;
	int size_class;
	int density_class;
	char succession_class[2];

	ponderosa = fopen("N:\\Visual_Basic\\2007_Surface_3017.txt","r");		//These two are now obsolete
	fout = fopen("N:\\Visual_Basic\\2007_Surface_3017_Output.txt","w");		//

	fgets(header,sizeof(header), ponderosa);								//Need to fgets new DatabaseProcessing.cpp output

	i = 0;
	j = 0;// Counts the number of stands

	while(!feof(ponderosa))
	{
		fscanf(ponderosa, "%d %d %d %lf %lf %lf %lf\n", &plots[i].tree_cn, &plots[i].year, &plots[i].species, &plots[i].tree_count, &plots[i].dbh, &plots[i].ba_acre, &plots[i].cover);	//Need to change
		if(i>0 && plots[i].year != plots[i-1].year)
		{
			j++;
		}
		i++;
	}

	fclose(ponderosa);

	i = 0;
	k = 0;
	l = 0;

	total1 = 0;
	total2 = 0;
	total3 = 0;
	pp_tpa21 = 0;
	lp_tpa21 = 0;
	other_tpa21 = 0;
	pp_cover21 = 0;
	lp_cover21 = 0;
	other_cover21 = 0;
	pp_cover5to21 = 0;
	lp_cover5to21 = 0;
	other_cover5to21 = 0;
	pp_cover0to5 = 0;
	lp_cover0to5 = 0;
	other_cover0to5 = 0;

	fprintf(fout, "tree_cn year ponderosa lodgepole other total_cover total_percent_cover ponderosa_percent lodgepole_percent other_percent pp_tpa21 lp_tpa21 other_tpa21 total_tpa21 pp_cover21 lp_cover21 other_cover21 total_cover21 total_cover21_percent pp_cover5to21 lp_cover5to21 other_cover5to21 total_cover5to21 total_cover5to21_percent pp_cover0to5 lp_cover0to5 other_cover0to5 total_cover0to5 total_cover0to5_percent size_class density_class succession_class\n");

		while(k<=j)
		{
		int year_count = plots[i].year;
		int tree_cn_count = plots[i].tree_cn;

			while(plots[i].year == year_count)
			{
				pp_tpa21 = 0;
				pp_cover21 = 0;
				pp_cover5to21 = 0;
				pp_cover0to5 = 0;

					if(plots[i].species == 1)
						{
							total1 = 0;

							while(plots[i].species == 1 && plots[i].year == year_count)
							{
								total1 = total1 + plots[i].cover;

								if(plots[i].dbh >= 21)
								{
									pp_tpa21 = pp_tpa21 + plots[i].tree_count;
									pp_cover21 = pp_cover21 + plots[i].cover;
								}

								else if(plots[i].dbh >= 5 && plots[i].dbh < 21)
								{
									pp_cover5to21 = pp_cover5to21 + plots[i].cover;
								}

								else
								{
									pp_cover0to5 = pp_cover0to5 + plots[i].cover;
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

						if(plots[i].species == 2)
						{
							total2 = 0;
				
							while(plots[i].species == 2 && plots[i].year == year_count)
							{
								total2 = total2 + plots[i].cover;

								if(plots[i].dbh >= 21)
								{
									lp_tpa21 = lp_tpa21 + plots[i].tree_count;
									lp_cover21 = lp_cover21 + plots[i].cover;
								}

								else if(plots[i].dbh >= 5 && plots[i].dbh < 21)
								{
									lp_cover5to21 = lp_cover5to21 + plots[i].cover;
								}

								else
								{
									lp_cover0to5 = lp_cover0to5 + plots[i].cover;
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


						if(plots[i].species > 2)
						{
							total3 = 0;
				
							while(plots[i].species > 2 && plots[i].year == year_count)
							{
								total3 = total3 + plots[i].cover;

								if(plots[i].dbh >= 21)
								{
									other_tpa21 = other_tpa21 + plots[i].tree_count;
									other_cover21 = other_cover21 + plots[i].cover;
								}

								else if(plots[i].dbh >= 5 && plots[i].dbh < 21)
								{
									other_cover5to21 = other_cover5to21 + plots[i].cover;
								}

								else
								{
									other_cover0to5 = other_cover0to5 + plots[i].cover;
								}

								i++;
							}
						}
						else
						{
							total3 = 0;
						}
				
		}
		k++;
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
			sprintf(succession_class,"A"); //Can I just put a in place of "A"?  Same for the rest of the classes..."B"=2, "C"=3...
		}
		else if(size_class == 2 && density_class == 1)
		{
			sprintf(succession_class,"C");
		}
		else if(size_class == 2 && density_class == 2)
		{
			sprintf(succession_class,"B");
		}
		else if(size_class == 3 && density_class == 1)
		{
			sprintf(succession_class,"D");
		}
		else
		{
			sprintf(succession_class,"E");
		}



		
		fprintf(fout, "%d %d %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %d %d %s\n", 
			tree_cn_count, year_count, total1, total2, total3, total, 
			total_percent_cover, percent_ponderosa, percent_lodgepole, percent_other, 
			pp_tpa21, lp_tpa21, other_tpa21, total_tpa21,
			pp_cover21, lp_cover21, other_cover21, total_cover21, total_cover21_percent,
			pp_cover5to21, lp_cover5to21, other_cover5to21, total_cover5to21, total_cover5to21_percent,
			pp_cover0to5, lp_cover0to5, other_cover0to5, total_cover0to5, total_cover0to5_percent,
			size_class, density_class, succession_class);
	}
	
}