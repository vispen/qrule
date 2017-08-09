// Copyright (C) 2017 Pelagicore
//
// You may use this file under the terms of the GPLv3 license.
// See the file LICENSE from this package for details.
//
// SPDX-License-Identifier: GPL-3.0

#include <QDebug>
#include "testsuite.h"

int main(int argv, char *argc[]) {

        /* QRuleEngine [options] qrule files

          1. Run QRuleEngine with rule against file to be tested, name the output file.

          1.1 Map the rule against the file and check if they are ok.

          2. if the rule passed then do nothing. if the rule did not pass save the out put and display it.
        */

        TestSuite *t = new TestSuite();
        t->runTestSuite();
        delete t;
}


