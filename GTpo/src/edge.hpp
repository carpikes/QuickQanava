/*
 Copyright (c) 2008-2018, Benoit AUTHEMAN All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the author or Destrat.io nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL AUTHOR BE LIABLE FOR ANY
 DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

//-----------------------------------------------------------------------------
// This file is a part of the GTpo software library.
//
// \file	edge.hpp
// \author	benoit@destrat.io
// \date	2016 01 22
//-----------------------------------------------------------------------------

namespace gtpo { // ::gtpo

/* edge Restricted Hyper Edge Management *///-------------------------------
template <class config_t>
auto edge<config_t>::addInHEdge( weak_edge_t inHEdge ) -> void
{
    if ( inHEdge.expired() )
        throw gtpo::bad_topology_error( "gtpo::edge<>::addInHEdge(): Error: Input hyper edge is null." );
    shared_edge_t inHEdgePtr{ inHEdge.lock() };
    if ( inHEdgePtr != nullptr ) {
        if ( inHEdgePtr->getHDst().expired() )
            inHEdgePtr->setHDst( this->shared_from_this() );
        config_t::template container_adapter< weak_edges_t >::insert( inHEdge, _inHEdges );
        if ( !inHEdgePtr->getSrc().expired() )
            config_t::template container_adapter< weak_node_ts >::insert( inHEdgePtr->getSrc(), _inHNodes );
    }
}

template < class config_t >
auto edge<config_t>::removeInHEdge( weak_edge_t inHEdge ) -> void
{
    if ( inHEdge.expired() )
        return;                 // Do not throw, removing a null inHEdge let edge in a perfectely valid state
    shared_edge_t inHEdgePtr{ inHEdge.lock() };
    if ( inHEdgePtr != nullptr ) {
        inHEdgePtr->setHDst( shared_edge_t{} );
        config_t::template container_adapter< weak_edges_t >::remove( inHEdge, _inHEdges );
        config_t::template container_adapter< weak_node_ts >::remove( inHEdgePtr->getSrc(), _inHNodes );
    }
}
//-----------------------------------------------------------------------------

} // ::gtpo
