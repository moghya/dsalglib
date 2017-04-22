//
// Created by moghya_s on 12/26/2016.
//

#ifndef DSALGLIB_GRAPH_H
#define DSALGLIB_GRAPH_H
#include "linklist.h"
#include "stack.h"
#include "queue.h"
#include "array.h"


namespace dsa
{
    template<class type>
    class graph
    {
    private:

        long long int count;
        long long int vindex;
        struct arc
        {
            long long int end;
            long long int cost;

            arc(long long int gvertex,long long int weight)
            {
                end=gvertex;
                cost=weight;
            }
            arc()
            {

            }

            bool operator==(arc temp)
            {
                if(end==temp.end&&cost==temp.cost)
                    return true;
                else return false;
            }
        };

        struct gnode
        {
            type data;
            long long int index;
            linklist<arc> outadj;
            linklist<arc> inadj;

            gnode(type param,long long int tindex)
            {
                data = param;
                index = tindex;
            }
            gnode()
            {

            }
        };

        linklist<gnode> nodes;

        long long int _getindex(type param)
        {
            long long int i,size=nodes.size();
            for(i=0;i<size;i++)
            {
                if(nodes[i].data==param) return i;
            }
            return -1;
        }

        long long int _getby_vindex(long long int tvindex)
        {
            long long int i;
            for(i=0;i<=tvindex;i++)
            {    if(nodes[i].index==tvindex)
                    return i;
            }
            return -1;

        }

    public:
        graph()
        {
            count=0;
            vindex = 0;
        }

        bool add_vertex(type param)
        {
            if(_getindex(param)>-1)
                return false;

            gnode vertex(param,vindex);
            nodes.add_back(vertex);
            count++;
            vindex++;
            return true;
        }

        bool add_arc(type from,type to,long long int weight=0)
        {
            long long int findex=-1,tindex=-1;

            findex=_getindex(from);
            tindex=_getindex(to);

            if(findex<0||tindex<0) return false;
            arc edge(nodes[tindex].index,weight);

            if(nodes[findex].outadj.search(edge)>=0)
                return false;

            nodes[findex].outadj.add_back(edge);

            edge.end = nodes[findex].index;
            nodes[tindex].inadj.add_back(edge);

            return true;

        }

        bool dfstraverse(type param,void (fun)(type obj))
        {
            array<bool> visited(count,false);
            long long int sindex = _getindex(param),temp,i,atemp;
            stack<long long int> s;
            if(sindex>-1)
            {
                s.push(sindex);
                visited[sindex]=true;
                while(!s.isempty())
                {
                    temp = s.pop();
                    fun(nodes[temp].data);
                    for(i=0;i<nodes[temp].outadj.size();i++)
                    {
                        atemp = _getby_vindex(nodes[temp].outadj[i].end);
                        if(!visited[atemp])
                        {
                            s.push(atemp);
                            visited[atemp]=true;
                        }
                    }
                }
                return true;
            }
            else
                return false;
        }

        bool bfstraverse(type param,void (fun)(type obj))
        {
            array<bool> visit(count,false);
            long long int sindex = _getindex(param),temp,i,atemp;
            queue<long long int> q;
            if(sindex>-1)
            {
                q.enqueue(sindex);
                visit[sindex]=true;
                while(!q.isempty())
                {
                    temp = q.dequeue();
                    fun(nodes[temp].data);
                    for(i=0;i<nodes[temp].outadj.size();i++)
                    {
                        atemp = _getby_vindex(nodes[temp].outadj[i].end);
                        if(!visit[atemp])
                        {
                            q.enqueue(atemp);
                            visit[atemp]=true;
                        }
                    }
                }
                return true;
            }
            else
                return false;
        }

        bool remove_vertex(type param)
        {
            long long int tindex = _getindex(param),i,size,tvindex;
            if(tindex<0)    return false;

            arc temparc;

            size = nodes[tindex].outadj.size();
            for(i=0;i<size;i++)
            {
                temparc = nodes[tindex].outadj[i];
                tvindex = _getby_vindex(temparc.end);
                nodes[tvindex].inadj.remove(temparc);
            }

            size = nodes[tindex].inadj.size();
            for(i=0;i<size;i++)
            {
                temparc = nodes[tindex].inadj[i];
                tvindex = _getby_vindex(temparc.end);
                nodes[tvindex].outadj.remove(temparc);
            }
            nodes.remove_at(tindex);
            return true;
        }


    };
}
#endif //DSALGLIB_GRAPH_H
