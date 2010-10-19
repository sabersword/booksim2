// $Id$

/*
Copyright (c) 2007-2009, Trustees of The Leland Stanford Junior University
All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

Redistributions of source code must retain the above copyright notice, this list
of conditions and the following disclaimer.
Redistributions in binary form must reproduce the above copyright notice, this 
list of conditions and the following disclaimer in the documentation and/or 
other materials provided with the distribution.
Neither the name of the Stanford University nor the names of its contributors 
may be used to endorse or promote products derived from this software without 
specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND 
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR 
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON 
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS 
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "switch_monitor.hpp"

#include "flit.hpp"

SwitchMonitor::SwitchMonitor( int inputs, int outputs ) {
  _cycles  = 0 ;
  _inputs  = inputs ;
  _outputs = outputs ;
  const int n = (inputs+1) * (outputs+1) * Flit::NUM_FLIT_TYPES ;
  _event.resize(n, 0) ;
}

int SwitchMonitor::index( int input, int output, int flitType ) const {
  return flitType + Flit::NUM_FLIT_TYPES * ( output + _outputs * input ) ;
}

void SwitchMonitor::cycle() {
  _cycles++ ;
}

void SwitchMonitor::traversal( int input, int output, Flit* flit ) {
  _event[ index( input, output, flit->type) ]++ ;
}

ostream& operator<<( ostream& os, const SwitchMonitor& obj ) {
  for ( int i = 0 ; i < obj._inputs ; i++ ) {
    for ( int o = 0 ; o < obj._outputs ; o++) {
      os << "[" << i << " -> " << o << "] " ;
      for ( int f = 0 ; f < Flit::NUM_FLIT_TYPES ; f++ ) {
	os << f << ":" << obj._event[ obj.index(i,o,f)] << " " ;
      }
      os << endl ;
    }
  }
  return os ;
}