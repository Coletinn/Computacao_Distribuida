// Gustavo Coleto de Freitas 32076541
// João Vitor Teles Centrone 32033125

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char **argv)
{
	double resultado_thread = 0, soma_global = 0;
	int inicio_thread, soma_local, id_thread, numero_thread, valor = 100000000;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&numero_thread);
	MPI_Comm_rank(MPI_COMM_WORLD,&id_thread);
  
	soma_local = valor/numero_thread;
  
	if(id_thread == 0)
  {
		int start;
		for (int i = 1; i < numero_thread; i++)
    {
			start = soma_local * i + 1;
            MPI_Send(&start, 1, MPI_INT, i, 0, MPI_COMM_WORLD);	
		}
		inicio_thread = soma_local * id_thread + 1;
	}
	else
  {
		MPI_Recv(&inicio_thread, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);	
	}
	for (int i = inicio_thread; i <= inicio_thread + soma_local; i++)
	{ 
		if(i > 100000000)
    {
			break;
		}
		double t = i;
		resultado_thread += 1 / t;
	}	
    MPI_Send(&resultado_thread, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);	
	if(id_thread == 0)
  {
		soma_global = resultado_thread;
		for(int i = 1; i < numero_thread; i++)
    {
			MPI_Recv(&resultado_thread, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			soma_global += resultado_thread;
		}
		printf("A soma eh: %f\n",soma_global);
	}
	MPI_Finalize();
	return 0;
}
