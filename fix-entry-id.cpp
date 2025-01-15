/*-
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * Copyright (c) 2025 NKI/AVL, Netherlands Cancer Institute
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <cif++.hpp>
#include <gxrio.hpp>

#include <filesystem>
#include <fstream>

// --------------------------------------------------------------------

int main(int argc, char *const argv[])
{
	if (argc < 3 or argc > 4)
	{
		std::cerr << "Usage: fix-id input new-id [output]\n";
		return 1;
	}

	gxrio::ifstream in(argv[1]);

	if (not in.is_open())
	{
		std::cerr << "Failed to open input file\n";
		return 1;
	}

	cif::file file(in);
	if (file.size() != 1)
	{
		std::cerr << "File does not have exactly one datablock\n";
		return 1;
	}

	file.load_dictionary("mmcif_pdbx;dssp-extension");
	if (not const_cast<const cif::file &>(file).is_valid())
		std::clog << "File is not a valid mmCIF file\n";

	auto &db = file.front();

	if (db.get("entry") == nullptr)
	{
		std::clog << "Datablock does not have an entry category\n";
		return 1;
	}

	// --------------------------------------------------------------------

	db.set_name(argv[2]);
	db["entry"].front().assign("id", argv[2], true);

	// that should have updated everything

	if (argc == 3)
		std::cout << file << "\n";
	else
		file.save(argv[3]);

	return 0;
}