# ThreeBeesBeta.c
/*****************************************************************************/
//Artificial Bee Colony Algorithm
//Main Object:
//Minimize the Objective Function
/*****************************************************************************/

/***********************************************************************************/
EMPLOYED BEE PHASE 
/***********************************************************************************/
FIRST:
//A randomly chosen solution is used in producing a mutant solution of the solution i
//and randomly selected solution must be different from the solution i
-->sol(Param2Change)=Foods(i,Param2Change)+(Foods(i,Param2Change)-Foods(neighbour,Param2Change))*(rand-0.5)*2;
//shifted onto the boundaries if generated parameter value is out of boundaries
//evaluate new solution
THEN:
//a greedy selection is applied between the current solution i and its mutant
//If the mutant solution is better than the current solution i, 
//replace the solution with the mutant and reset the trial counter of solution i
//if the solution i can not be improved, increase its trial counter

/***********************************************************************************/
//Calculate Probabilities 
//A food source is chosen with the probability which is proportioal to its quality
/***********************************************************************************/
for (i = 0;i<FoodNumber;i++)
	{
		NectarSource[i].rfitness = (0.9*(NectarSource[i].fitness / maxfit)) + 0.1;
	}
  
/***********************************************************************************/
//ONLOOKER BEE PHASE 
/***********************************************************************************/
//A food source is chosen with the probability which is proportioal to its quality
NEXT SAME AS EMPLOYED

//--------------->MemorizeBestSource();
/*****************************************************************************/
//SCOUT BEE PHASE
//determine the food sources whose trial counter exceeds the "limit" value
//only one scout is allowed to occur in each cycle
/*****************************************************************************/

//determine the food sources whose trial counter exceeds the "limit" value

//--------------->MemorizeBestSource();

/*****************************************************************************/
COUT<<<<<<<<<<<<<<<<<<<<<<,OVER
/*****************************************************************************/
