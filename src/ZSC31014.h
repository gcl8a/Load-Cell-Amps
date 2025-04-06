/**
 * A library for the ZSC31014 load cell amplifier, as found on, for example, the ...
 */

#pragma once

#include <LoadCell.h>

class ZSC31014 : public LoadCellAmp
{

public:
    virtual bool Init(void);

    // For requesting a measurement when in sleep mode
    bool MeasurementRequest(bool specialMeasurements = false);

    // For fetching data (optionally with temperature info...what to do with it?)
    int16_t FetchData(bool getTempCoeff = false);

    void StartCommandMode(void);
    void StartNormalOperationMode(void);
    void SetOffset(uint16_t);
    void SetGain(uint16_t);
    void SetPreampGain(uint16_t);
};

