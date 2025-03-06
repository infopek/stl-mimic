#pragma once

#include <linked_list.h>
#include <hash_table.h>
#include <vector.h>

#include <stdexcept>
#include <iostream>

namespace core {
    template <typename T>
    struct Edge {
        T u;
        T v;
        float weight;
    };

    template <typename T>
    class Graph {
    public:
        virtual ~Graph() = default;

        virtual Vector<T> vertices() const = 0;
        virtual Vector<Edge<T>> edges() const = 0;
        virtual Vector<T> neighbors(const T& vertex) const = 0;

        virtual void addEdge(const T& src, const T& dest, float weight = 0.0f) = 0;
        virtual void addVertex(const T& vertex) = 0;
        virtual void removeVertex(const T& vertex) = 0;
        virtual void removeEdge(const T& src, const T& dest) = 0;

        virtual bool containsVertex(const T& vertex) const = 0;
        virtual bool containsEdge(const T& src, const T& dest) const = 0;
    };

    template <typename T>
    class UGraph : public Graph<T> {
    public:
        UGraph() {
        }
        ~UGraph() = default;

        Vector<T> vertices() const override {
            Vector<T> vertices{};
            vertices.reserve(m_adjList.size());
            for (const auto& [v, list] : m_adjList) {
                vertices.pushBack(v);
            }
            return vertices;
        }
        Vector<Edge<T>> edges() const override {
            Vector<Edge<T>> edges{};
            for (const auto& [v, list] : m_adjList) {
                for (const auto& e : list) {
                    edges.pushBack(e);
                }
            }
            return edges;
        }
        Vector<T> neighbors(const T& vertex) const override {
            return {};
        }

        void addEdge(const T& src, const T& dest, float weight = 0.0f) override {
            if (!containsVertex(src) || !containsVertex(dest)) {
                throw std::invalid_argument("One or both of the provided vertices do not exist in graph");
            }
            if (containsEdge(src, dest)) {
                throw std::invalid_argument("Edge already exists in graph");
            }

            // Undirected, so add edge from src to dest and vica-versa
            m_adjList[src].pushBack(Edge{
                .u = src,
                .v = dest,
                .weight = weight
                });
            m_adjList[dest].pushBack(Edge{
                .u = dest,
                .v = src,
                .weight = weight
                });
        }
        void addVertex(const T& vertex) override {
            if (containsVertex(vertex)) {
                throw std::invalid_argument("Vertex already exists in graph");
            }

            m_adjList[vertex] = SLinkedList<Edge<T>>();
        }
        void removeEdge(const T& src, const T& dest) override {

        }
        void removeVertex(const T& vertex) override {

        }


        bool containsVertex(const T& vertex) const override {
            return m_adjList.contains(vertex);
        }

        /// Assumes that `src` and `dest` are in the graph
        bool containsEdge(const T& src, const T& dest) const override {
            // Graph is undirected, so it contains neither or both -> enough to check src->dest 
            if (const auto& list = m_adjList.get(src)) {
                for (const auto& e : *list) {
                    if (e.v == dest) {
                        return true;
                    }
                }
            }
            return false;
        }
    private:
        HashTable<T, SLinkedList<Edge<T>>> m_adjList{};
    };
}