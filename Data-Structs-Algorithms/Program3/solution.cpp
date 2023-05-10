/*
	File Name: solution.cpp
	Author: Lord Smaul
	Date: 03/10/2023
	Purpose: Brute-force solution to the Traveling Salesman Problem using an adjacency matrix
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>
#include <list>

#include <cstddef>
#include <cstring>

typedef std::size_t vertex_t;
typedef std::tuple<vertex_t, vertex_t, double> weighted_edge_t;

/* Get the source of a weighted edge.
 *
 * This function returns the source of a weighted edge.
 *
 * @param edge - the edge
 *
 * @return std::get<0>(edg)
 * */
vertex_t get_source(const weighted_edge_t &edg);

/* Get the destination of a weighted edge.
 *
 * This function returns the destination of a weighted edge.
 *
 * @param edge - the edge
 *
 * @return std::get<1>(edg)
 * */
vertex_t get_destination(const weighted_edge_t &edg);

/* Get the weight of a weighted edge.
 *
 * This function returns the weight of a weighted edge.
 *
 * @param edge - the edge
 *
 * @return std::get<2>(edg)
 * */
vertex_t get_weight(const weighted_edge_t &edg);

/* Determine the number of vertices in the graph.
 *
 * This function determines the number of vertices in the graph represented
 * by a vector of weighted edges. It is assumed that the number of vertices
 * is given by the largest source or destination vertex in the list of edges
 * plus one.
 *
 * @param edges - a vector of weighted edges defining a graph
 *
 * @return the number of vertices in the graph represented by edges
 * */
unsigned int get_vertex_count(const std::vector<weighted_edge_t> &edges);

/* Reads weighted edges from a file.
 *
 * This function reads weighted edges from filename and returns them as a
 * std::vector<weighted_edge_t>. each line of the file is assumed to be of the
 * form "src dst wt" where src is the source vertex, and dst is the destination
 * vertex, and wt is the weight of the edge. All vertices are assumed to be
 * unsigned integers that can be stored as a std::size_t (i.e., in a vertex_t).
 * Duplicate edges found in the file are ignored.
 *
 * @param filename - name of the file to read
 *
 * @return a vector of edges read from filename
 *
 * @throws std::runtime_error - thrown if there is an error reading the file
 * */
std::vector<weighted_edge_t> read_graph(const std::string &filename);

/* Solves the traveling salesman problem by brute force.
 *
 * This function solves the TSP via brute force. It accepts a vector of
 * weighted edges and count of the number of vertices. These two values
 * together define a weighted graph.
 *
 * @param edges - a vector of weighted edges in the graph
 *
 * @param n_vertices - the number of vertices in the graph;
 *                     the vertices are 0 ... n_vertices-1
 *
 * @return the cost of the minimum Hamiltonian cycle or infinity if none exists
 * */
double TSP(const std::vector<weighted_edge_t> &edges, unsigned int n_vertices);

// Helper function for filling the adjacency matrix with 0s
std::vector<std::vector<double>> fillAdjMatrix(unsigned int n)
{
	std::vector<std::vector<double>> am;

	for (unsigned int i = 0; i < n; i++)
	{
		// Used to read in the weights for each vecotr in the vector
		std::vector<double> v1;

		for (unsigned int j = 0; j < n; j++)
		{
			v1.push_back(0);
		}

		// Push back the inner vector into the outer vector
		am.push_back(v1);
	}

	return am;
}

double TSP(const std::vector<weighted_edge_t> &edges, unsigned int n_vertices)
{
	/* IMPLEMENT THIS FUNCTION */
	double min_cost = std::numeric_limits<double>::infinity();
	// Initalize a vector of vectors of doubles from helper function
	std::vector<std::vector<double>> adj_matrix = fillAdjMatrix(n_vertices);

	// Fill adjacency matrix with weight values
	for (unsigned int i = 0; i < edges.size(); i++)
	{
		adj_matrix[get_source(edges.at(i))][get_destination(edges.at(i))] = get_weight(edges.at(i));
	}

	std::vector<int> vertex; // Used to build a vertex list to develop the permutaitions

	// Fills a vector with all vertexes of each row of the matrix
	for (unsigned int j = 0; j < n_vertices; j++)
	{
		vertex.push_back(j);
	}

	// Determines if a Hamiltonian Cycle exists
	for (unsigned int i = 0; i < n_vertices; i++)
	{
		// Determines Hamiltonian Cycle from permuatations of the vertex vector
		do
		{
			double pathWeight = 0; // Path weight of each permutation
			int index = i;		   // Used to pull source index without changing the source variable itself
			bool valid = true;

			// Builds path weight
			for (unsigned int k = 0; k < vertex.size(); k++)
			{
				double weight = adj_matrix[index][vertex[k]];
				if (weight == 0)
				{
					valid = false;
					break;
				}
				pathWeight += weight; // Adds weight of each vertex along the cycle
				index = vertex[k];	  // Sets new index to jump to in the cycle
			}
			if (valid)
			{
				pathWeight += adj_matrix[index][i];		   // Adds the vertex back to the source to the path weight
				min_cost = std::min(min_cost, pathWeight); // Updates the minimum path weight
			}

		} while (next_permutation(vertex.begin(), vertex.end()));
	}

	return min_cost;
}

vertex_t get_source(const weighted_edge_t &edg)
{
	return std::get<0>(edg);
}

vertex_t get_destination(const weighted_edge_t &edg)
{
	return std::get<1>(edg);
}

vertex_t get_weight(const weighted_edge_t &edg)
{
	return std::get<2>(edg);
}

unsigned int get_vertex_count(const std::vector<weighted_edge_t> &edges)
{
	unsigned int n_vertices = 0;
	if (!edges.empty())
	{
		std::set<vertex_t> vertex_set;

		/* add the source vertices to vertex_set */
		std::transform(
			edges.begin(),
			edges.end(),
			std::inserter(vertex_set, vertex_set.end()),
			get_source);

		/* add the destination vertices to vertex_set */
		std::transform(
			edges.begin(),
			edges.end(),
			std::inserter(vertex_set, vertex_set.end()),
			get_destination);

		/* get the largest vertex from vertex_set and add 1 */
		n_vertices = *std::max_element(vertex_set.begin(), vertex_set.end()) + 1;
	}

	return n_vertices;
}

std::vector<weighted_edge_t> read_graph(const std::string &filename)
{
	std::vector<weighted_edge_t> edges;
	std::ifstream file(filename);
	if (file)
	{
		/* read edges into a set to remove duplicates */
		std::set<weighted_edge_t> edge_set;

		vertex_t src, dst;
		double wt;
		while (file >> src && file >> dst && file >> wt)
		{
			edge_set.insert(weighted_edge_t(src, dst, wt));
		}

		/* check if there was an error reading in the file */
		if (file.bad())
		{ // i/o error
			std::ostringstream oss;
			oss << filename << ": " << strerror(errno);
			throw std::runtime_error(oss.str());
		}
		else if ((file.fail() && !file.eof()))
		{ // conversion error
			std::ostringstream oss;
			oss << filename << ": error reading file";
			throw std::runtime_error(oss.str());
		}

		/* copy the edges read to the edges vector */
		std::copy(edge_set.begin(), edge_set.end(), std::back_inserter(edges));
	}
	else
	{ // error opening file
		std::ostringstream oss;
		oss << filename << ": " << strerror(errno);
		throw std::runtime_error(oss.str());
	}

	if (edges.empty())
	{
		std::ostringstream oss;
		oss << filename << ": file does not contain any edges";
		throw std::runtime_error(oss.str());
	}
	return edges;
}

void usage(int argc, char *argv[])
{
	if (argc != 2)
	{
		std::cerr << "Invalid number of command line arguments." << std::endl
				  << std::endl;
	}
	std::cout << "usage: ";
	std::cout << argv[0] << " infile" << std::endl;
	std::cout << "  infile - file containing a list of edges" << std::endl
			  << std::endl;
	std::cout << "It is assumed that each line of <infile> contains an edge of the" << std::endl;
	std::cout << "form <src> <dst> <wt>." << std::endl;
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		usage(argc, argv);
	}
	else
	{
		try
		{
			std::vector<weighted_edge_t> edges = read_graph(argv[1]);
			unsigned int n_vertices = get_vertex_count(edges);
			double min_cost = TSP(edges, n_vertices);
			if (min_cost == std::numeric_limits<double>::infinity())
			{
				std::cout << "No Hamiltonian cycle exists." << std::endl;
			}
			else
			{
				std::cout << min_cost << std::endl;
			}
		}
		catch (std::exception &ex)
		{
			std::cerr << ex.what() << std::endl;
		}
	}

	return 0;
}
