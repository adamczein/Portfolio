#include "AffichageMemoire.h"
#include "memoire_24.h"
#ifndef BYTECODE_H
#define BYTECONE_H

class ByteCode{
    public:
        ByteCode();
        void LectureByteCode();
        int getTaille() const;
    private:
        int taille_;
};
#endif
