/* 
 *  Algorithm Pseudocode:
 *
 1  Algorithm  Kosaraju(G,v)
 2  Input : G=(V,E),)
 3  Output : strongly connected component (SCC)
 4  begin
 5      while(stack does not contain all vertices)
 6         Choose an arbitrary vertex v not in S
 7         Depth First Search(G,V)
 8         Each time that depth-first search finishes expanding a vertex u, push u onto S
 9      compute GT
10      While(stack is not empty)
11           pop vertex v form stack
12           Depth First Search(GT,v)
13           Output set of visited vertices as a seprate SCC 
14           mark this set of vertices form stack and graph 
12  end
*/

import java.util.ArrayList;

public class Kosaraju {

   private ArrayList<Node> stack;

   public ArrayList<ArrayList<Node>> getSCC(Node root, AdjacencyList list){
       stack = new ArrayList<Node>();

       // search the graph (depth-first search), adding nodes to the stack
       search(root, list, true);

       // reverse all the edges in the graph
       list.reverseGraph();

       // search the graph again in the stack's order
       ArrayList<ArrayList<Node>> SCC = new ArrayList<ArrayList<Node>>();
       while(!stack.isEmpty()){
           ArrayList<Node> component = new ArrayList<Node>();
           search(stack.get(0), list, false);

           // any components we visited are strongly connected
           // remove them from the stack and add them to the component
           for(Iterator<Node> it = stack.iterator(); it.hasNext(); ){
               Node n = it.next();
               if(!n.visited){
                   component.add(n);
                   it.remove();
               }
           }

           // add the component to the result set
           SCC.add(component);
       }
       return SCC;
   }

   private void search(Node root, AdjacencyList list, boolean forward){
       root.visited = forward;
       if(list.getAdjacent(root) == null){
           if(forward) stack.add(0, root);
           return;
       }
       for(Edge e : list.getAdjacent(root)){
           if(e.to.visited != forward){
               search(e.to, list, forward);
           }
       }
       if(forward) stack.add(0, root);
   }
}
