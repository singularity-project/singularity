// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "core.h"
#include "protocol.h"
#include "util.h"

//
// Main network
//

unsigned int pnSeed[] =
{
    0x12345678
};

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        pchMessageStart[0] = 0xd6;
        pchMessageStart[1] = 0x82;
        pchMessageStart[2] = 0x41;
        pchMessageStart[3] = 0xfa;
        vAlertPubKey = ParseHex("04a82e43bebee0af77bb6d4f830c5b2095b7479a480e91bbbf3547fb261c5e6d1be2c27e3c57503f501480f5027371ec62b2be1b6f00fc746e4b3777259e7f6a78");
        nDefaultPort = 20345;
        nRPCPort = 20346;
        bnProofOfWorkLimit[ALGO_SCRYPT]  = CBigNum(~uint256(0) >> 20);
        bnProofOfWorkLimit[ALGO_X13]   = CBigNum(~uint256(0) >> 20);
        nSubsidyHalvingInterval = 80000;

        // Build the genesis block. Note that the output of the genesis coinbase cannot
        // be spent as it did not originally exist in the database.
  
        const char* pszTimestamp = "NYTIMES 27/06 Ukraine Signs Trade Agreement With European Union";
        CTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CBigNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 1000 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04e941763c7750969e751bee1ffbe96a651a0feb131db046546c219ea40bff40b95077dc9ba1c05af991588772d8daabbda57386c068fb9bc7477c5e28702d5eb9") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = BLOCK_VERSION_DEFAULT;
        genesis.nTime    = 1403865879;
        genesis.nBits    = 0x1e0fffff;
        genesis.nNonce   = 2093686841;
        
        //// debug print
        hashGenesisBlock = genesis.GetHash();
        //while (hashGenesisBlock > bnProofOfWorkLimit[ALGO_SCRYPT].getuint256()){
        //    if (++genesis.nNonce==0) break;
        //    hashGenesisBlock = genesis.GetHash();
        //}

        //printf("MAIN: %s\n", hashGenesisBlock.ToString().c_str());
        //printf("%s\n", genesis.hashMerkleRoot.ToString().c_str());
        //printf("%x\n", bnProofOfWorkLimit[ALGO_SCRYPT].GetCompact());
        //genesis.print();
        
        assert(hashGenesisBlock == uint256("0x000004cb17262360e82c8a766954b6492ef72e544ef6befc89b95697c35645cb"));
        assert(genesis.hashMerkleRoot == uint256("0x769281adbeadd216ae817c687d3d618ae3660cd932b21100c0d8c44528b11147"));

        vSeeds.push_back(CDNSSeedData("seed1.singularity.org", "seed1.singularity.org"));
        vSeeds.push_back(CDNSSeedData("seed2.singularity.org", "seed2.singularity.org"));
        vSeeds.push_back(CDNSSeedData("seed3.singularity.org", "seed3.singularity.org"));
        vSeeds.push_back(CDNSSeedData("seed4.singularity.org", "seed4.singularity.org"));

        base58Prefixes[PUBKEY_ADDRESS] = 63;
        base58Prefixes[SCRIPT_ADDRESS] = 9;
        base58Prefixes[SECRET_KEY] = 178;

        // Convert the pnSeeds array into usable address objects.
        for (unsigned int i = 0; i < ARRAYLEN(pnSeed); i++)
        {
            // It'll only connect to one or two seed nodes because once it connects,
            // it'll get a pile of addresses with newer timestamps.
            // Seed nodes are given a random 'last seen time' 
            const int64 nTwoDays = 2 * 24 * 60 * 60;
            struct in_addr ip;
            memcpy(&ip, &pnSeed[i], sizeof(ip));
            CAddress addr(CService(ip, GetDefaultPort()));
            addr.nTime = GetTime() - GetRand(nTwoDays) - nTwoDays;
            vFixedSeeds.push_back(addr);
        }
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet (v3)
//
class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        pchMessageStart[0] = 0xaa;
        pchMessageStart[1] = 0xab;
        pchMessageStart[2] = 0xb5;
        pchMessageStart[3] = 0x83;
        vAlertPubKey = ParseHex("044adf046e6bc86fb83ef92f261fa3feff9176bd029c5ad4afb5c52ac21f9851f2b2eb861cdbf2c09e0cb97dbf75c6ca5ff6c5df88cfb244c72dba1d44b5a47655");
        nDefaultPort = 21345;
        nRPCPort = 21346;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1403865966;
        genesis.nNonce = 417451273;
        
        //// debug print
        hashGenesisBlock = genesis.GetHash();
        //while (hashGenesisBlock > bnProofOfWorkLimit[ALGO_SCRYPT].getuint256()){
        //    if (++genesis.nNonce==0) break;
        //   hashGenesisBlock = genesis.GetHash();
        //}

        //printf("TEST: %s\n", hashGenesisBlock.ToString().c_str());
        //printf("%s\n", genesis.hashMerkleRoot.ToString().c_str());
        // genesis.print();
        
        assert(hashGenesisBlock == uint256("0x0000063b032d3e9637b4b32ba568e72f14bd8a8310d017c733926b6a078750e6"));

        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("testseed1.singularity.org", "testseed1.singularity.org"));

        base58Prefixes[PUBKEY_ADDRESS] = 88;
        base58Prefixes[SCRIPT_ADDRESS] = 188;
        base58Prefixes[SECRET_KEY] = 239;

    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0x55;
        pchMessageStart[1] = 0x7a;
        pchMessageStart[2] = 0xbb;
        pchMessageStart[3] = 0xf9;
        nSubsidyHalvingInterval = 150;
        bnProofOfWorkLimit[ALGO_SCRYPT]  = CBigNum(~uint256(0) >> 1);
        bnProofOfWorkLimit[ALGO_X13]   = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1403865967;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 5;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 21401;
        strDataDir = "regtest";
        
        //// debug print
        hashGenesisBlock = genesis.GetHash();
        //while (hashGenesisBlock > bnProofOfWorkLimit[ALGO_SCRYPT].getuint256()){
        //    if (++genesis.nNonce==0) break;
        //    hashGenesisBlock = genesis.GetHash();
        //}

        //printf("REG: %s\n", hashGenesisBlock.ToString().c_str());
        //printf("%s\n", genesis.hashMerkleRoot.ToString().c_str());
        genesis.print();

        assert(hashGenesisBlock == uint256("0x77e8425fe4d9bf653f5ba5d95ab4f777d51f79b7507bd2855a9e058b017e3a0c"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.

        base58Prefixes[PUBKEY_ADDRESS] = 0;
        base58Prefixes[SCRIPT_ADDRESS] = 5;
        base58Prefixes[SECRET_KEY] = 128;
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
