// The Serpentine Caves
// Copyright (c) 2011, 2012 Christopher Claudio Capobianco
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * The name of Christopher Claudio Capobianco may not be used to endorse
//       or promote products derived from this software without specific prior
//       written permission.
//
// THIS SOFTWARE IS PROVIDED BY CHRISTOPHER CLAUDIO CAPOBIANCO ``AS IS'' AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL CHRISTOPHER CLAUDIO CAPOBIANCO BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Copyright (c) 2009 J.C.Wilk
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * The name of J.C.Wilk may not be used to endorse or promote products
//       derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY J.C.WILK ``AS IS'' AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL J.C.WILK BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "Main.hpp"

const char *tmp[] = {"Dead", "Dying", "Wounded", "Injured", "Healthy"};
vector<string> Status::bodilyStatus(tmp, tmp + 5);

const char *tmp2[] = {"Burdened", "Poisoned", "Weakened", "Sluggish", "Feeble", "Confused"};
vector<string> Status::ailmentStatus(tmp2, tmp2 + 6);

// The Assignment Operator
Stats &Stats::operator= (const Stats &rhs)
{
	// Do the compound assignment work
	this->hpmax = rhs.hpmax;
	//this->hpmax = Clamp<int>(this->hpmax, HPMIN, HPMAX);

	this->ap    = rhs.ap;
	//this->ap    = Clamp<int>(this->ap, APMIN, APMAX);

	this->dp    = rhs.dp;
	//this->dp    = Clamp<int>(this->dp, DPMIN, DPMAX);

	this->str   = rhs.str;
	//this->str   = Clamp<int>(this->str, STRMIN, STRMAX);

	this->spd   = rhs.spd;
	//this->spd   = Clamp<int>(this->spd, SPDMIN, SPDMAX);

	this->mpmax = rhs.mpmax;
	//this->mpmax = Clamp<int>(this->mpmax, MPMIN, MPMAX);

	this->map   = rhs.map;
	//this->map   = Clamp<int>(this->map, MAPMIN, MAPMAX);

	this->mdp   = rhs.mdp;
	//this->mdp   = Clamp<int>(this->mdp, MDPMIN, MDPMAX);

	this->wil   = rhs.wil;
	//this->wil   = Clamp<int>(this->wil, WILMIN, WILMAX);

	this->acu   = rhs.acu;
	//this->acu   = Clamp<int>(this->acu, ACUMIN, ACUMAX);

	return *this;
}

// The Compound Assignment Operator
Stats &Stats::operator+= (const Stats &rhs)
{
	// Do the compound assignment work
	this->hpmax += rhs.hpmax;
	this->hpmax = Clamp<int>(this->hpmax, HPMIN, HPMAX);

	this->ap    += rhs.ap;
	this->ap    = Clamp<int>(this->ap, APMIN, APMAX);

	this->dp    += rhs.dp;
	this->dp    = Clamp<int>(this->dp, DPMIN, DPMAX);

	this->str   += rhs.str;
	this->str   = Clamp<int>(this->str, STRMIN, STRMAX);

	this->spd   += rhs.spd;
	this->spd   = Clamp<int>(this->spd, SPDMIN, SPDMAX);

	this->mpmax += rhs.mpmax;
	this->mpmax = Clamp<int>(this->mpmax, MPMIN, MPMAX);

	this->map   += rhs.map;
	this->map   = Clamp<int>(this->map, MAPMIN, MAPMAX);

	this->mdp   += rhs.mdp;
	this->mdp   = Clamp<int>(this->mdp, MDPMIN, MDPMAX);

	this->wil   += rhs.wil;
	this->wil   = Clamp<int>(this->wil, WILMIN, WILMAX);

	this->acu   += rhs.acu;
	this->acu   = Clamp<int>(this->acu, ACUMIN, ACUMAX);

	return *this;
}

// The Compound Assignment Operator
Stats &Stats::operator-= (const Stats &rhs)
{
	// Do the compound assignment work
	this->hpmax -= rhs.hpmax;
	this->hpmax = Clamp<int>(this->hpmax, HPMIN, HPMAX);

	this->ap    -= rhs.ap;
	this->ap    = Clamp<int>(this->ap, APMIN, APMAX);

	this->dp    -= rhs.dp;
	this->dp    = Clamp<int>(this->dp, DPMIN, DPMAX);

	this->str   -= rhs.str;
	this->str   = Clamp<int>(this->str, STRMIN, STRMAX);

	this->spd   -= rhs.spd;
	this->spd   = Clamp<int>(this->spd, SPDMIN, SPDMAX);

	this->mpmax -= rhs.mpmax;
	this->mpmax = Clamp<int>(this->mpmax, MPMIN, MPMAX);

	this->map   -= rhs.map;
	this->map   = Clamp<int>(this->map, MAPMIN, MAPMAX);

	this->mdp   -= rhs.mdp;
	this->mdp   = Clamp<int>(this->mdp, MDPMIN, MDPMAX);

	this->wil   -= rhs.wil;
	this->wil   = Clamp<int>(this->wil, WILMIN, WILMAX);

	this->acu   -= rhs.acu;
	this->acu   = Clamp<int>(this->acu, ACUMIN, ACUMAX);

	return *this;
}

// The Assignment Operator
Status &Status::operator= (const Status &rhs)
{
	// Do the compound assignment work
	this->hp = rhs.hp;
	//this->hp = Clamp<int>(this->hp, 0, HPMAX);
	this->mp = rhs.mp;
	//this->mp = Clamp<int>(this->mp, 0, MPMAX);

	return *this;
}

// The Compound Assignment Operator
Status &Status::operator+= (const Status &rhs)
{
	// Do the compound assignment work
	this->hp += rhs.hp;
	this->hp = Clamp<int>(this->hp, 0, HPMAX);
	this->mp += rhs.mp;
	this->mp = Clamp<int>(this->mp, 0, MPMAX);

	return *this;
}

// The Compound Assignment Operator
Status &Status::operator-= (const Status &rhs)
{
	// Do the compound assignment work
	this->hp -= rhs.hp;
	this->hp = Clamp<int>(this->hp, 0, HPMAX);
	this->mp -= rhs.mp;
	this->mp = Clamp<int>(this->mp, 0, MPMAX);

	return *this;
}