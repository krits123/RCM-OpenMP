
#include <boost/config.hpp>
#include <vector>
#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cuthill_mckee_ordering.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/bandwidth.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
/*
  Sample Output
  original bandwidth: 8
  Reverse Cuthill-McKee ordering starting at: 6
    8 3 0 9 2 5 1 4 7 6
    bandwidth: 4
  Reverse Cuthill-McKee ordering starting at: 0
    9 1 4 6 7 2 8 5 3 0
    bandwidth: 4
  Reverse Cuthill-McKee ordering:
    0 8 5 7 3 6 4 2 1 9
    bandwidth: 4
 */

 void readFile(const char* file_name, int* row,int *col, int n)
 {
 	FILE* fptr = fopen(file_name, "r");
 	if (fptr == NULL) {
 		printf("Could not opent he file. Exiting...\n");
 		exit(-1);
 	}
 	else {
    fread(row,sizeof(int),n,fptr);
    fread(col,sizeof(int),n,fptr);
    fclose(fptr);
 	}
 }


int main(int argc,char* argv[])
{
  using namespace boost;
  using namespace std;
  typedef adjacency_list<vecS, vecS, undirectedS,
     property<vertex_color_t, default_color_type,
       property<vertex_degree_t,int> > > Graph;
  typedef graph_traits<Graph>::vertex_descriptor Vertex;
  typedef graph_traits<Graph>::vertices_size_type size_type;

  typedef std::pair<std::size_t, std::size_t> Pair;
	struct timeval startwtime, endwtime;
	double seq_time;



  if(argc!=4){

    printf("You need to give 3 arguments :\n1.Number o vertexes\n2.Number of non zero values\n3.Input file name\n");
    exit(1);
  }
  int n = atoi(argv[1]);
  int nnz = atoi(argv[2]);

  printf("Woriking with file %s\n", argv[3]);
	//int n = 28924;
  //int nnz = 2043492;
	int *row =(int*)malloc(nnz*sizeof(int));
  int *col =(int*)malloc(nnz*sizeof(int));
	//readFile("matBucky1.bin",B,n);
  //readFile("large.bin",row,col,nnz);
  readFile(argv[3],row,col,nnz);



  Graph G(n);
  for (int i = 0; i < nnz; ++i){
        int r = row[i];
        int c = col[i];
				add_edge(r,c,G);
		}
    //add_edge(edges[i].first, edges[i].second, G);
 free(row);
 free(col);
  graph_traits<Graph>::vertex_iterator ui, ui_end;

  gettimeofday(&startwtime, NULL);
  property_map<Graph,vertex_degree_t>::type deg = get(vertex_degree, G);
  for (boost::tie(ui, ui_end) = vertices(G); ui != ui_end; ++ui)
    deg[*ui] = degree(*ui, G);

  property_map<Graph, vertex_index_t>::type
    index_map = get(vertex_index, G);

//  std::cout << "original bandwidth: " << bandwidth(G) << std::endl;

  std::vector<Vertex> inv_perm(num_vertices(G));
  std::vector<size_type> perm(num_vertices(G));
  {
    Vertex s = vertex(6, G);
    //reverse cuthill_mckee_ordering

		
    cuthill_mckee_ordering(G, s, inv_perm.rbegin(), get(vertex_color, G),
                           get(vertex_degree, G));


	 gettimeofday( &endwtime, NULL );
   seq_time = (double)( ( endwtime.tv_usec - startwtime.tv_usec ) / 1.0e6 + endwtime.tv_sec - startwtime.tv_sec );
   printf("Sequential method time is %f secconds.\n",seq_time );
    /* cout << "Reverse Cuthill-McKee ordering starting at: " << s << endl;
    cout << "  ";
    for (std::vector<Vertex>::const_iterator i = inv_perm.begin();
         i != inv_perm.end(); ++i)
      cout << index_map[*i] << " ";
    cout << endl;

    for (size_type c = 0; c != inv_perm.size(); ++c)
      perm[index_map[inv_perm[c]]] = c;
    std::cout << "  bandwidth: "
              << bandwidth(G, make_iterator_property_map(&perm[0], index_map, perm[0]))
              << std::endl;
  }
  {
    Vertex s = vertex(0, G);
    //reverse cuthill_mckee_ordering
    cuthill_mckee_ordering(G, s, inv_perm.rbegin(), get(vertex_color, G),
                           get(vertex_degree, G));
    cout << "Reverse Cuthill-McKee ordering starting at: " << s << endl;
    cout << "  ";
    for (std::vector<Vertex>::const_iterator i=inv_perm.begin();
       i != inv_perm.end(); ++i)
      cout << index_map[*i] << " ";
    cout << endl;

    for (size_type c = 0; c != inv_perm.size(); ++c)
      perm[index_map[inv_perm[c]]] = c;
    std::cout << "  bandwidth: "
              << bandwidth(G, make_iterator_property_map(&perm[0], index_map, perm[0]))
              << std::endl;
  }

  {
    //reverse cuthill_mckee_ordering
    cuthill_mckee_ordering(G, inv_perm.rbegin(), get(vertex_color, G),
                           make_degree_map(G));

    cout << "Reverse Cuthill-McKee ordering:" << endl;
    cout << "  ";
    for (std::vector<Vertex>::const_iterator i=inv_perm.begin();
       i != inv_perm.end(); ++i)
      cout << index_map[*i] << " ";
    cout << endl;

    for (size_type c = 0; c != inv_perm.size(); ++c)
      perm[index_map[inv_perm[c]]] = c;
    std::cout << "  bandwidth: "
              << bandwidth(G, make_iterator_property_map(&perm[0], index_map, perm[0]))
              << std::endl;
							*/
  }
  return 0;
}
