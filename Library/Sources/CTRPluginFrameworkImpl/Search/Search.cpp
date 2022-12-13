#include <Headers.hpp>

namespace CTRPluginFramework {
    void Search32::FirstSearchSpecifiedU8(u32 endAddress, SearchFlags compare, Results32 *result) {
        switch (compare) {
            case SearchFlags::Equal: {
                while (_currentAddress <= endAddress && _resultsInPool < _maxResults) {
                    u8 value = *(u8*)_currentAddress;

                    if (EQ(value, _checkValue.U8)) {
                        *result++ = {_currentAddress, value};
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    _currentAddress++;
                }

                break;
            }

            case SearchFlags::NotEqual: {
                while (_currentAddress <= endAddress && _resultsInPool < _maxResults) {
                    u8 value = *(u8*)_currentAddress;

                    if (NE(value, _checkValue.U8)) {
                        *result++ = {_currentAddress, value};
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    _currentAddress++;
                }

                break;
            }

            case SearchFlags::GreaterThan: {
                while (_currentAddress <= endAddress && _resultsInPool < _maxResults) {
                    u8 value = *(u8*)_currentAddress;

                    if (GT(value, _checkValue.U8)) {
                        *result++ = {_currentAddress, value};
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    _currentAddress++;
                }

                break;
            }

            case SearchFlags::GreaterOrEqual: {
                while (_currentAddress <= endAddress && _resultsInPool < _maxResults) {
                    u8 value = *(u8*)_currentAddress;

                    if (GE(value, _checkValue.U8)) {
                        *result++ = {_currentAddress, value};
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    _currentAddress++;
                }

                break;
            }

            case SearchFlags::LesserThan: {
                while (_currentAddress <= endAddress && _resultsInPool < _maxResults) {
                    u8 value = *(u8*)_currentAddress;

                    if (LT(value, _checkValue.U8)) {
                        *result++ = {_currentAddress, value};
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    _currentAddress++;
                }

                break;
            }

            case SearchFlags::LesserOrEqual: {
                while (_currentAddress <= endAddress && _resultsInPool < _maxResults) {
                    u8 value = *(u8*)_currentAddress;

                    if (LE(value, _checkValue.U8)) {
                        *result++ = {_currentAddress, value};
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    _currentAddress++;
                }

                break;
            }

            default: break;
        }
    }

    void Search32::FirstSearchSpecifiedU16(u32 endAddress, SearchFlags compare, Results32 *result) {
        switch (compare) {
            case SearchFlags::Equal: {
                while (_currentAddress <= endAddress && _resultsInPool < _maxResults) {
                    u16 value = *(u16*)_currentAddress;

                    if (EQ(value, _checkValue.U16)) {
                        *result++ = {_currentAddress, value = value};
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    _currentAddress += 2;
                }

                break;
            }

            case SearchFlags::NotEqual: {
                while (_currentAddress <= endAddress && _resultsInPool < _maxResults) {
                    u16 value = *(u16*)_currentAddress;

                    if (NE(value, _checkValue.U16)) {
                        *result++ = {_currentAddress, value};
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    _currentAddress += 2;
                }

                break;
            }

            case SearchFlags::GreaterThan: {
                while (_currentAddress <= endAddress && _resultsInPool < _maxResults) {
                    u16 value = *(u16*)_currentAddress;

                    if (GT(value, _checkValue.U16)) {
                        *result++ = {_currentAddress, value};
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    _currentAddress += 2;
                }

                break;
            }

            case SearchFlags::GreaterOrEqual: {
                while (_currentAddress <= endAddress && _resultsInPool < _maxResults) {
                    u16 value = *(u16*)_currentAddress;

                    if (GE(value, _checkValue.U16)) {
                        *result++ = {_currentAddress, value};
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    _currentAddress += 2;
                }

                break;
            }

            case SearchFlags::LesserThan: {
                while (_currentAddress <= endAddress && _resultsInPool < _maxResults) {
                    u16 value = *(u16*)_currentAddress;

                    if (LT(value, _checkValue.U16)) {
                        *result++ = {_currentAddress, value};
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    _currentAddress += 2;
                }

                break;
            }

            case SearchFlags::LesserOrEqual: {
                while (_currentAddress <= endAddress && _resultsInPool < _maxResults) {
                    u16 value = *(u16*)_currentAddress;

                    if (LE(value, _checkValue.U16)) {
                        *result++ = {_currentAddress, value};
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    _currentAddress += 2;
                }

                break;
            }

            default: break;
        }
    }

    void Search32::FirstSearchSpecifiedU32(u32 endAddress, SearchFlags compare, Results32 *result) {
        switch (compare) {
            case SearchFlags::Equal: {
                while (_currentAddress <= endAddress && _resultsInPool < _maxResults) {
                    u32 value = *(u32*)_currentAddress;

                    if (EQ(value, _checkValue.U32)) {
                        *result++ = {_currentAddress, value};
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    _currentAddress += 4;
                }

                break;
            }

            case SearchFlags::NotEqual: {
                while (_currentAddress <= endAddress && _resultsInPool < _maxResults) {
                    u32 value = *(u32*)_currentAddress;

                    if (NE(value, _checkValue.U32)) {
                        *result++ = {_currentAddress, value};
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    _currentAddress += 4;
                }

                break;
            }

            case SearchFlags::GreaterThan: {
                while (_currentAddress <= endAddress && _resultsInPool < _maxResults) {
                    u32 value = *(u32*)_currentAddress;

                    if (GT(value, _checkValue.U32)) {
                        *result++ = {_currentAddress, value};
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    _currentAddress += 4;
                }

                break;
            }

            case SearchFlags::GreaterOrEqual: {
                while (_currentAddress <= endAddress && _resultsInPool < _maxResults) {
                    u32 value = *(u32*)_currentAddress;

                    if (GE(value, _checkValue.U32)) {
                        *result++ = {_currentAddress, value};
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    _currentAddress += 4;
                }

                break;
            }

            case SearchFlags::LesserThan: {
                while (_currentAddress <= endAddress && _resultsInPool < _maxResults) {
                    u32 value = *(u32*)_currentAddress;

                    if (LT(value, _checkValue.U32)) {
                        *result++ = {_currentAddress, value};
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    _currentAddress += 4;
                }

                break;
            }

            case SearchFlags::LesserOrEqual: {
                while (_currentAddress <= endAddress && _resultsInPool < _maxResults) {
                    u32 value = *(u32*)_currentAddress;

                    if (LE(value, _checkValue.U32)) {
                        *result++ = {_currentAddress, value};
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    _currentAddress += 4;
                }

                break;
            }

            default: break;
        }
    }

    // From https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/
    bool AlmostEqualRelative(float A, float B, float maxRelDiff) {
        // Calculate the difference.
        float diff = fabs(A - B);
        A = fabs(A);
        B = fabs(B);
        // Find the largest
        float largest = (B > A) ? B : A;
        return diff <= maxRelDiff * largest;
    }

    void Search32::FirstSearchSpecifiedFloat(u32 endAddress, SearchFlags compare, Results32 *result) {
        switch (compare) {
            case SearchFlags::Equal: {
                while (_currentAddress <= endAddress && _resultsInPool < _maxResults) {
                    float value = *(float*)_currentAddress;

                    if (FP_EQ(value, _checkValue.Float)) {
                        result->address = _currentAddress;
                        result++->value.Float = value;
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    _currentAddress += 4;
                }

                break;
            }

            case SearchFlags::NotEqual: {
                while (_currentAddress <= endAddress && _resultsInPool < _maxResults) {
                    float value = *(float*)_currentAddress;

                    if (FP_NE(value, _checkValue.Float)) {
                        result->address = _currentAddress;
                        result++->value.Float = value;
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    _currentAddress += 4;
                }

                break;
            }

            case SearchFlags::GreaterThan: {
                while (_currentAddress <= endAddress && _resultsInPool < _maxResults) {
                    float value = *(float*)_currentAddress;

                    if (FP_GT(value, _checkValue.Float)) {
                        result->address = _currentAddress;
                        result++->value.Float = value;
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    _currentAddress += 4;
                }

                break;
            }

            case SearchFlags::GreaterOrEqual: {
                while (_currentAddress <= endAddress && _resultsInPool < _maxResults) {
                    float value = *(float*)_currentAddress;

                    if (FP_GE(value, _checkValue.Float)) {
                        result->address = _currentAddress;
                        result++->value.Float = value;
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    _currentAddress += 4;
                }

                break;
            }

            case SearchFlags::LesserThan: {
                while (_currentAddress <= endAddress && _resultsInPool < _maxResults) {
                    float value = *(float*)_currentAddress;

                    if (FP_LT(value, _checkValue.Float)) {
                        result->address = _currentAddress;
                        result++->value.Float = value;
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    _currentAddress += 4;
                }

                break;
            }

            case SearchFlags::LesserOrEqual: {
                while (_currentAddress <= endAddress && _resultsInPool < _maxResults) {
                    float value = *(float*)_currentAddress;

                    if (FP_LE(value, _checkValue.Float)) {
                        result->address = _currentAddress;
                        result++->value.Float = value;
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    _currentAddress += 4;
                }

                break;
            }

            default: break;
        }
    }

    void Search32::SecondSearchSpecifiedU8(Storage<Results32> &data, SearchFlags compare, Results32WithOld *result) {
        u8 checkValue = _checkValue.U8;

        // If current search is specified
        if (IsSpecifiedSearch(_flags)) {
            switch (compare)
            {
                case SearchFlags::Equal: {
                    for (Results32 &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u8 newValue = *(u8*)res.address;
                        u8 oldValue = res.value.U8;

                        if (EQ(newValue, checkValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::NotEqual: {
                    for (Results32 &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u8 newValue = *(u8*)res.address;
                        u8 oldValue = res.value.U8;

                        if (NE(newValue, checkValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::GreaterThan: {
                    for (Results32 &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u8 newValue = *(u8*)res.address;
                        u8 oldValue = res.value.U8;

                        if (GT(newValue, checkValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::GreaterOrEqual: {
                    for (Results32 &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u8 newValue = *(u8*)res.address;
                        u8 oldValue = res.value.U8;

                        if (GE(newValue, checkValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::LesserThan: {
                    for (Results32 &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u8 newValue = *(u8*)res.address;
                        u8 oldValue = res.value.U8;

                        if (LT(newValue, checkValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::LesserOrEqual: {
                    for (Results32 &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u8 newValue = *(u8*)res.address;
                        u8 oldValue = res.value.U8;

                        if (LE(newValue, checkValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::DifferentBy: {
                    for (Results32 &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u8 newValue = *(u8*)res.address;
                        u8 oldValue = res.value.U8;

                        if (DB(newValue, oldValue, _checkValue.U8)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::DifferentByLess: {
                    for (Results32 &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u8 newValue = *(u8*)res.address;
                        u8 oldValue = res.value.U8;

                        if (DBL(newValue, oldValue, _checkValue.U8)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::DifferentByMore: {
                    for (Results32 &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u8 newValue = *(u8*)res.address;
                        u8 oldValue = res.value.U8;

                        if (DBM(newValue, oldValue, _checkValue.U8)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                default: break;
            }
        }

        // Else for unknown search
        else {
            switch (compare) {
                case SearchFlags::Equal: {
                    for (Results32 &res : data) {
                        u8 newValue = *(u8*)res.address;
                        u8 oldValue = res.value.U8;

                        if (EQ(newValue, oldValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::NotEqual: {
                    for (Results32 &res : data) {
                        u8 newValue = *(u8*)res.address;
                        u8 oldValue = res.value.U8;

                        if (NE(newValue, oldValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::GreaterThan: {
                    for (Results32 &res : data) {
                        u8 newValue = *(u8*)res.address;
                        u8 oldValue = res.value.U8;

                        if (GT(newValue, oldValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::GreaterOrEqual: {
                    for (Results32 &res : data) {
                        u8 newValue = *(u8*)res.address;
                        u8 oldValue = res.value.U8;

                        if (GE(newValue, oldValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::LesserThan: {
                    for (Results32 &res : data) {
                        u8 newValue = *(u8*)res.address;
                        u8 oldValue = res.value.U8;

                        if (LT(newValue, oldValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::LesserOrEqual: {
                    for (Results32 &res : data) {
                        u8 newValue = *(u8*)res.address;
                        u8 oldValue = res.value.U8;

                        if (LE(newValue, oldValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::DifferentBy: {
                    for (Results32 &res : data) {
                        u8 newValue = *(u8*)res.address;
                        u8 oldValue = res.value.U8;

                        if (DB(newValue, oldValue, _checkValue.U8)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::DifferentByLess: {
                    for (Results32 &res : data) {
                        u8 newValue = *(u8*)res.address;
                        u8 oldValue = res.value.U8;

                        if (DBL(newValue, oldValue, _checkValue.U8)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::DifferentByMore: {
                    for (Results32 &res : data) {
                        u8 newValue = *(u8*)res.address;
                        u8 oldValue = res.value.U8;

                        if (DBM(newValue, oldValue, _checkValue.U8)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                default: break;
            }

        }
    }

    void Search32::SecondSearchSpecifiedU16(Storage<Results32> &data, SearchFlags compare, Results32WithOld *result) {
        u16 checkValue = _checkValue.U16;

        // If current search is specified
        if (IsSpecifiedSearch(_flags)) {
            switch (compare) {
                case SearchFlags::Equal: {
                    for (Results32 &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u16 newValue = *(u16*)res.address;
                        u16 oldValue = res.value.U16;

                        if (EQ(newValue, checkValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress += 2;
                    }

                    break;
                }

                case SearchFlags::NotEqual: {
                    for (Results32 &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u16 newValue = *(u16*)res.address;
                        u16 oldValue = res.value.U16;

                        if (NE(newValue, checkValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress += 2;
                    }

                    break;
                }

                case SearchFlags::GreaterThan: {
                    for (Results32 &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u16 newValue = *(u16*)res.address;
                        u16 oldValue = res.value.U16;

                        if (GT(newValue, checkValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress += 2;
                    }

                    break;
                }

                case SearchFlags::GreaterOrEqual: {
                    for (Results32 &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u16 newValue = *(u16*)res.address;
                        u16 oldValue = res.value.U16;

                        if (GE(newValue, checkValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress += 2;
                    }

                    break;
                }

                case SearchFlags::LesserThan: {
                    for (Results32 &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u16 newValue = *(u16*)res.address;
                        u16 oldValue = res.value.U16;

                        if (LT(newValue, checkValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress += 2;
                    }

                    break;
                }

                case SearchFlags::LesserOrEqual: {
                    for (Results32 &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u16 newValue = *(u16*)res.address;
                        u16 oldValue = res.value.U16;

                        if (LE(newValue, checkValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress += 2;
                    }

                    break;
                }

                case SearchFlags::DifferentBy: {
                    for (Results32 &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u16 newValue = *(u16*)res.address;
                        u16 oldValue = res.value.U16;

                        if (DB(newValue, oldValue, _checkValue.U16)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress += 2;
                    }

                    break;
                }

                case SearchFlags::DifferentByLess: {
                    for (Results32 &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u16 newValue = *(u16*)res.address;
                        u16 oldValue = res.value.U16;

                        if (DBL(newValue, oldValue, _checkValue.U16)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress += 2;
                    }

                    break;
                }

                case SearchFlags::DifferentByMore: {
                    for (Results32 &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u16 newValue = *(u16*)res.address;
                        u16 oldValue = res.value.U16;

                        if (DBM(newValue, oldValue, _checkValue.U16)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress += 2;
                    }

                    break;
                }

                default: break;
            }
        }

        // Else for unknown search
        else {
            switch (compare) {
                case SearchFlags::Equal: {
                    for (Results32 &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u16 newValue = *(u16*)res.address;
                        u16 oldValue = res.value.U16;

                        if (EQ(newValue, oldValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress += 2;
                    }

                    break;
                }

                case SearchFlags::NotEqual: {
                    for (Results32 &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u16 newValue = *(u16*)res.address;
                        u16 oldValue = res.value.U16;

                        if (NE(newValue, oldValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress += 2;
                    }

                    break;
                }

                case SearchFlags::GreaterThan: {
                    for (Results32 &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u16 newValue = *(u16*)res.address;
                        u16 oldValue = res.value.U16;

                        if (GT(newValue, oldValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress += 2;
                    }

                    break;
                }

                case SearchFlags::GreaterOrEqual: {
                    for (Results32 &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u16 newValue = *(u16*)res.address;
                        u16 oldValue = res.value.U16;

                        if (GE(newValue, oldValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress += 2;
                    }

                    break;
                }

                case SearchFlags::LesserThan: {
                    for (Results32 &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u16 newValue = *(u16*)res.address;
                        u16 oldValue = res.value.U16;

                        if (LT(newValue, oldValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress += 2;
                    }

                    break;
                }

                case SearchFlags::LesserOrEqual: {
                    for (Results32 &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u16 newValue = *(u16*)res.address;
                        u16 oldValue = res.value.U16;

                        if (LE(newValue, oldValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress += 2;
                    }

                    break;
                }

                case SearchFlags::DifferentBy: {
                    for (Results32 &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u16 newValue = *(u16*)res.address;
                        u16 oldValue = res.value.U16;

                        if (DB(newValue, oldValue, _checkValue.U16)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress += 2;
                    }

                    break;
                }

                case SearchFlags::DifferentByLess: {
                    for (Results32 &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u16 newValue = *(u16*)res.address;
                        u16 oldValue = res.value.U16;

                        if (DBL(newValue, oldValue, _checkValue.U16)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress += 2;
                    }

                    break;
                }

                case SearchFlags::DifferentByMore: {
                    for (Results32 &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u16 newValue = *(u16*)res.address;
                        u16 oldValue = res.value.U16;

                        if (DBM(newValue, oldValue, _checkValue.U16)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress += 2;
                    }

                    break;
                }

                default: break;
            }
        }
    }

    void Search32::SecondSearchSpecifiedU32(Storage<Results32> &data, SearchFlags compare, Results32WithOld *result) {
        u32 checkValue = _checkValue.U32;

        // If current search is specified
        if (IsSpecifiedSearch(_flags)) {
            switch (compare) {
                case SearchFlags::Equal: {
                    for (Results32 &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u32 newValue = *(u32*)res.address;
                        u32 oldValue = res.value.U32;

                        if (EQ(newValue, checkValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::NotEqual: {
                    for (Results32 &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u32 newValue = *(u32*)res.address;
                        u32 oldValue = res.value.U32;

                        if (NE(newValue, checkValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::GreaterThan: {
                    for (Results32 &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u32 newValue = *(u32*)res.address;
                        u32 oldValue = res.value.U32;

                        if (GT(newValue, checkValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::GreaterOrEqual: {
                    for (Results32 &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u32 newValue = *(u32*)res.address;
                        u32 oldValue = res.value.U32;

                        if (GE(newValue, checkValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::LesserThan: {
                    for (Results32 &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u32 newValue = *(u32*)res.address;
                        u32 oldValue = res.value.U32;

                        if (LT(newValue, checkValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::LesserOrEqual: {
                    for (Results32 &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u32 newValue = *(u32*)res.address;
                        u32 oldValue = res.value.U32;

                        if (LE(newValue, checkValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::DifferentBy: {
                    for (Results32 &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u32 newValue = *(u32*)res.address;
                        u32 oldValue = res.value.U32;

                        if (DB(newValue, oldValue, _checkValue.U32)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::DifferentByLess: {
                    for (Results32 &res : data) {
                        u32 newValue = *(u32*)res.address;
                        u32 oldValue = res.value.U32;

                        if (DBL(newValue, oldValue, _checkValue.U32)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::DifferentByMore: {
                    for (Results32 &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u32 newValue = *(u32*)res.address;
                        u32 oldValue = res.value.U32;

                        if (DBM(newValue, oldValue, _checkValue.U32)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                default: break;
            }
        }

        // Else for unknown search
        else {
            switch (compare) {
                case SearchFlags::Equal: {
                    for (Results32 &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u32 newValue = *(u32*)res.address;
                        u32 oldValue = res.value.U32;

                        if (EQ(newValue, oldValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::NotEqual: {
                    for (Results32 &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u32 newValue = *(u32*)res.address;
                        u32 oldValue = res.value.U32;

                        if (NE(newValue, oldValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::GreaterThan: {
                    for (Results32 &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u32 newValue = *(u32*)res.address;
                        u32 oldValue = res.value.U32;

                        if (GT(newValue, oldValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::GreaterOrEqual: {
                    for (Results32 &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u32 newValue = *(u32*)res.address;
                        u32 oldValue = res.value.U32;

                        if (GE(newValue, oldValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::LesserThan: {
                    for (Results32 &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u32 newValue = *(u32*)res.address;
                        u32 oldValue = res.value.U32;

                        if (LT(newValue, oldValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::LesserOrEqual: {
                    for (Results32 &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u32 newValue = *(u32*)res.address;
                        u32 oldValue = res.value.U32;

                        if (LE(newValue, oldValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::DifferentBy: {
                    for (Results32 &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u32 newValue = *(u32*)res.address;
                        u32 oldValue = res.value.U32;

                        if (DB(newValue, oldValue, _checkValue.U32)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::DifferentByLess: {
                    for (Results32 &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u32 newValue = *(u32*)res.address;
                        u32 oldValue = res.value.U32;

                        if (DBL(newValue, oldValue, _checkValue.U32)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::DifferentByMore: {
                    for (Results32 &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u32 newValue = *(u32*)res.address;
                        u32 oldValue = res.value.U32;

                        if (DBM(newValue, oldValue, _checkValue.U32)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                default: break;
            }
        }
    }

    void Search32::SecondSearchSpecifiedFloat(Storage<Results32> &data, SearchFlags compare, Results32WithOld *result) {
        float checkValue = _checkValue.Float;

        // If current search is specified
        if (IsSpecifiedSearch(_flags)) {
            switch (compare) {
                case SearchFlags::Equal: {
                    for (Results32 &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        float newValue = *(float*)res.address;
                        float oldValue = res.value.Float;

                        if (FP_EQ(newValue, checkValue)) {
                            result->address = res.address;
                            result->newValue.Float = newValue;
                            result++->oldValue.Float = oldValue;
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::NotEqual: {
                    for (Results32 &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        float newValue = *(float*)res.address;
                        float oldValue = res.value.Float;

                        if (FP_NE(newValue, checkValue)) {
                            result->address = res.address;
                            result->newValue.Float = newValue;
                            result++->oldValue.Float = oldValue;
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::GreaterThan: {
                    for (Results32 &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        float newValue = *(float*)res.address;
                        float oldValue = res.value.Float;

                        if (FP_GT(newValue, checkValue)) {
                            result->address = res.address;
                            result->newValue.Float = newValue;
                            result++->oldValue.Float = oldValue;
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::GreaterOrEqual: {
                    for (Results32 &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        float newValue = *(float*)res.address;
                        float oldValue = res.value.Float;

                        if (FP_GE(newValue, checkValue)) {
                            result->address = res.address;
                            result->newValue.Float = newValue;
                            result++->oldValue.Float = oldValue;
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::LesserThan: {
                    for (Results32 &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        float newValue = *(float*)res.address;
                        float oldValue = res.value.Float;

                        if (FP_LT(newValue, checkValue)) {
                            result->address = res.address;
                            result->newValue.Float = newValue;
                            result++->oldValue.Float = oldValue;
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::LesserOrEqual: {
                    for (Results32 &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        float newValue = *(float*)res.address;
                        float oldValue = res.value.Float;

                        if (FP_LE(newValue, checkValue)) {
                            result->address = res.address;
                            result->newValue.Float = newValue;
                            result++->oldValue.Float = oldValue;
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::DifferentBy: {
                    for (Results32 &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        float newValue = *(float*)res.address;
                        float oldValue = res.value.Float;

                        if (IsValid(oldValue) && FP_DB(newValue, oldValue, _checkValue.Float)) {
                            result->address = res.address;
                            result->newValue.Float = newValue;
                            result++->oldValue.Float = oldValue;
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::DifferentByLess: {
                    for (Results32 &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        float newValue = *(float*)res.address;
                        float oldValue = res.value.Float;

                        if (IsValid(oldValue) && FP_DBL(newValue, oldValue, _checkValue.Float)) {
                            result->address = res.address;
                            result->newValue.Float = newValue;
                            result++->oldValue.Float = oldValue;
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::DifferentByMore: {
                    for (Results32 &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        float newValue = *(float*)res.address;
                        float oldValue = res.value.Float;

                        if (IsValid(oldValue) && FP_DBM(newValue, oldValue, _checkValue.Float)) {
                            result->address = res.address;
                            result->newValue.Float = newValue;
                            result++->oldValue.Float = oldValue;
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                default: break;
            }
        }

        // Else for unknown search
        else {
            switch (compare) {
                case SearchFlags::Equal: {
                    for (Results32 &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        float newValue = *(float*)res.address;
                        float oldValue = res.value.Float;

                        if (IsValid(oldValue) && FP_EQ(newValue, oldValue)) {
                            result->address = res.address;
                            result->newValue.Float = newValue;
                            result++->oldValue.Float = oldValue;
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::NotEqual: {
                    for (Results32 &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        float newValue = *(float*)res.address;
                        float oldValue = res.value.Float;

                        if (IsValid(oldValue) && FP_NE(newValue, oldValue)) {
                            result->address = res.address;
                            result->newValue.Float = newValue;
                            result++->oldValue.Float = oldValue;
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::GreaterThan: {
                    for (Results32 &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        float newValue = *(float*)res.address;
                        float oldValue = res.value.Float;

                        if (IsValid(oldValue) && FP_GT(newValue, oldValue)) {
                            result->address = res.address;
                            result->newValue.Float = newValue;
                            result++->oldValue.Float = oldValue;
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::GreaterOrEqual: {
                    for (Results32 &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        float newValue = *(float*)res.address;
                        float oldValue = res.value.Float;

                        if (IsValid(oldValue) && FP_GE(newValue, oldValue)) {
                            result->address = res.address;
                            result->newValue.Float = newValue;
                            result++->oldValue.Float = oldValue;
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::LesserThan: {
                    for (Results32 &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        float newValue = *(float*)res.address;
                        float oldValue = res.value.Float;

                        if (IsValid(oldValue) && FP_LT(newValue, oldValue)) {
                            result->address = res.address;
                            result->newValue.Float = newValue;
                            result++->oldValue.Float = oldValue;
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::LesserOrEqual: {
                    for (Results32 &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        float newValue = *(float*)res.address;
                        float oldValue = res.value.Float;

                        if (IsValid(oldValue) && FP_LE(newValue, oldValue)) {
                            result->address = res.address;
                            result->newValue.Float = newValue;
                            result++->oldValue.Float = oldValue;
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::DifferentBy: {
                    for (Results32 &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        float newValue = *(float*)res.address;
                        float oldValue = res.value.Float;

                        if (IsValid(oldValue) && FP_DB(newValue, oldValue, _checkValue.Float)) {
                            result->address = res.address;
                            result->newValue.Float = newValue;
                            result++->oldValue.Float = oldValue;
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::DifferentByLess: {
                    for (Results32 &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        float newValue = *(float*)res.address;
                        float oldValue = res.value.Float;

                        if (IsValid(oldValue) && FP_DBL(newValue, oldValue, _checkValue.Float)) {
                            result->address = res.address;
                            result->newValue.Float = newValue;
                            result++->oldValue.Float = oldValue;
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::DifferentByMore: {
                    for (Results32 &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        float newValue = *(float*)res.address;
                        float oldValue = res.value.Float;

                        if (IsValid(oldValue) && FP_DBM(newValue, oldValue, _checkValue.Float)) {
                            result->address = res.address;
                            result->newValue.Float = newValue;
                            result++->oldValue.Float = oldValue;
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                default: break;
            }
        }
    }

    void Search32::SecondSearchUnknownU8(Storage<u32> &data, SearchFlags compare, Results32WithOld *result) {
        u32 address = _startRegion + _currentAddress * 4;

        switch (compare) {
            case SearchFlags::Equal: {
                for (u32 v : data) {
                    if (_resultsInPool > _maxResults - 4)
                        break;

                    Bytes32 oldValue = {v};
                    Bytes32 newValue = {*(u32*)address};

                    if (EQ(newValue.b1, oldValue.b1)) {
                        *result++ = {address, newValue.b1, oldValue.b1};
                        ResultsCount++;
                        _resultsInPool++;
                    }

                    address++;

                    if (EQ(newValue.b2, oldValue.b2)) {
                        *result++ = {address, newValue.b2, oldValue.b2};
                        ResultsCount++;
                        _resultsInPool++;
                    }

                    address++;

                    if (EQ(newValue.b3, oldValue.b3)) {
                        *result++ = {address, newValue.b3, oldValue.b3};
                        ResultsCount++;
                        _resultsInPool++;
                    }

                    address++;

                    if (EQ(newValue.b4, oldValue.b4)) {
                        *result++ = {address, newValue.b4, oldValue.b4};
                        ResultsCount++;
                        _resultsInPool++;
                    }

                    address++;
                }

                break;
            }

            case SearchFlags::NotEqual: {
                for (u32 v : data) {
                    if (_resultsInPool > _maxResults - 4)
                        break;

                    Bytes32 oldValue = {v};
                    Bytes32 newValue = {*(u32*)address};

                    if (NE(newValue.b1, oldValue.b1)) {
                        *result++ = {address, newValue.b1, oldValue.b1};
                        ResultsCount++;
                        _resultsInPool++;
                    }

                    address++;

                    if (NE(newValue.b2, oldValue.b2)) {
                        *result++ = {address, newValue.b2, oldValue.b2};
                        ResultsCount++;
                        _resultsInPool++;
                    }

                    address++;

                    if (NE(newValue.b3, oldValue.b3)) {
                        *result++ = {address, newValue.b3, oldValue.b3};
                        ResultsCount++;
                        _resultsInPool++;
                    }

                    address++;

                    if (NE(newValue.b4, oldValue.b4)) {
                        *result++ = {address, newValue.b4, oldValue.b4};
                        ResultsCount++;
                        _resultsInPool++;
                    }

                    address++;
                }

                break;
            }

            case SearchFlags::GreaterThan: {
                for (u32 v : data) {
                    if (_resultsInPool > _maxResults - 4)
                        break;

                    Bytes32 oldValue = {v};
                    Bytes32 newValue = {*(u32*)address};

                    if (GT(newValue.b1, oldValue.b1)) {
                        *result++ = {address, newValue.b1, oldValue.b1};
                        ResultsCount++;
                        _resultsInPool++;
                    }

                    address++;

                    if (GT(newValue.b2, oldValue.b2)) {
                        *result++ = {address, newValue.b2, oldValue.b2};
                        ResultsCount++;
                        _resultsInPool++;
                    }

                    address++;

                    if (GT(newValue.b3, oldValue.b3)) {
                        *result++ = {address, newValue.b3, oldValue.b3};
                        ResultsCount++;
                        _resultsInPool++;
                    }

                    address++;

                    if (GT(newValue.b4, oldValue.b4)) {
                        *result++ = {address, newValue.b4, oldValue.b4};
                        ResultsCount++;
                        _resultsInPool++;
                    }

                    address++;
                }

                break;
            }

            case SearchFlags::GreaterOrEqual: {
                for (u32 v : data) {
                    if (_resultsInPool > _maxResults - 4)
                        break;

                    Bytes32 oldValue = {v};
                    Bytes32 newValue = {*(u32*)address};

                    if (GE(newValue.b1, oldValue.b1)) {
                        *result++ = {address, newValue.b1, oldValue.b1};
                        ResultsCount++;
                        _resultsInPool++;
                    }

                    address++;

                    if (GE(newValue.b2, oldValue.b2)) {
                        *result++ = {address, newValue.b2, oldValue.b2};
                        ResultsCount++;
                        _resultsInPool++;
                    }

                    address++;

                    if (GE(newValue.b3, oldValue.b3)) {
                        *result++ = {address, newValue.b3, oldValue.b3};
                        ResultsCount++;
                        _resultsInPool++;
                    }

                    address++;

                    if (GE(newValue.b4, oldValue.b4)) {
                        *result++ = {address, newValue.b4, oldValue.b4};
                        ResultsCount++;
                        _resultsInPool++;
                    }

                    address++;
                }

                break;
            }

            case SearchFlags::LesserThan: {
                for (u32 v : data) {
                    if (_resultsInPool > _maxResults - 4)
                        break;

                    Bytes32 oldValue = {v};
                    Bytes32 newValue = {*(u32*)address};

                    if (LT(newValue.b1, oldValue.b1)) {
                        *result++ = {address, newValue.b1, oldValue.b1};
                        ResultsCount++;
                        _resultsInPool++;
                    }

                    address++;

                    if (LT(newValue.b2, oldValue.b2)) {
                        *result++ = {address, newValue.b2, oldValue.b2};
                        ResultsCount++;
                        _resultsInPool++;
                    }

                    address++;

                    if (LT(newValue.b3, oldValue.b3)) {
                        *result++ = {address, newValue.b3, oldValue.b3};
                        ResultsCount++;
                        _resultsInPool++;
                    }

                    address++;

                    if (LT(newValue.b4, oldValue.b4)) {
                        *result++ = {address, newValue.b4, oldValue.b4};
                        ResultsCount++;
                        _resultsInPool++;
                    }

                    address++;
                }

                break;
            }

            case SearchFlags::LesserOrEqual: {
                for (u32 v : data) {
                    if (_resultsInPool > _maxResults - 4)
                        break;

                    Bytes32 oldValue = {v};
                    Bytes32 newValue = {*(u32*)address};

                    if (LE(newValue.b1, oldValue.b1)) {
                        *result++ = {address, newValue.b1, oldValue.b1};
                        ResultsCount++;
                        _resultsInPool++;
                    }

                    address++;

                    if (LE(newValue.b2, oldValue.b2)) {
                        *result++ = {address, newValue.b2, oldValue.b2};
                        ResultsCount++;
                        _resultsInPool++;
                    }

                    address++;

                    if (LE(newValue.b3, oldValue.b3)) {
                        *result++ = {address, newValue.b3, oldValue.b3};
                        ResultsCount++;
                        _resultsInPool++;
                    }

                    address++;

                    if (LE(newValue.b4, oldValue.b4)) {
                        *result++ = {address, newValue.b4, oldValue.b4};
                        ResultsCount++;
                        _resultsInPool++;
                    }

                    address++;
                }

                break;
            }

            case SearchFlags::DifferentBy: {
                u8 difference = _checkValue.U8;

                for (u32 v : data) {
                    if (_resultsInPool > _maxResults - 4)
                        break;

                    Bytes32 oldValue = {v};
                    Bytes32 newValue = {*(u32*)address};

                    if (DB(newValue.b1, oldValue.b1, difference)) {
                        *result++ = {address, newValue.b1, oldValue.b1};
                        ResultsCount++;
                        _resultsInPool++;
                    }

                    address++;

                    if (DB(newValue.b2, oldValue.b2, difference)) {
                        *result++ = {address, newValue.b2, oldValue.b2};
                        ResultsCount++;
                        _resultsInPool++;
                    }

                    address++;

                    if (DB(newValue.b3, oldValue.b3, difference)) {
                        *result++ = {address, newValue.b3, oldValue.b3};
                        ResultsCount++;
                        _resultsInPool++;
                    }

                    address++;

                    if (DB(newValue.b4, oldValue.b4, difference)) {
                        *result++ = {address, newValue.b4, oldValue.b4};
                        ResultsCount++;
                        _resultsInPool++;
                    }

                    address++;
                }

                break;
            }

            case SearchFlags::DifferentByLess: {
                u8 difference = _checkValue.U8;

                for (u32 v : data) {
                    if (_resultsInPool > _maxResults - 4)
                        break;

                    Bytes32 oldValue = {v};
                    Bytes32 newValue = {*(u32*)address};

                    if (DBL(newValue.b1, oldValue.b1, difference)) {
                        *result++ = {address, newValue.b1, oldValue.b1};
                        ResultsCount++;
                        _resultsInPool++;
                    }

                    address++;

                    if (DBL(newValue.b2, oldValue.b2, difference)) {
                        *result++ = {address, newValue.b2, oldValue.b2};
                        ResultsCount++;
                        _resultsInPool++;
                    }

                    address++;

                    if (DBL(newValue.b3, oldValue.b3, difference)) {
                        *result++ = {address, newValue.b3, oldValue.b3};
                        ResultsCount++;
                        _resultsInPool++;
                    }

                    address++;

                    if (DBL(newValue.b4, oldValue.b4, difference)) {
                        *result++ = {address, newValue.b4, oldValue.b4};
                        ResultsCount++;
                        _resultsInPool++;
                    }

                    address++;
                }

                break;
            }

            case SearchFlags::DifferentByMore: {
                u8 difference = _checkValue.U8;

                for (u32 v : data) {
                    if (_resultsInPool > _maxResults - 4)
                        break;

                    Bytes32 oldValue = {v};
                    Bytes32 newValue = {*(u32*)address};

                    if (DBM(newValue.b1, oldValue.b1, difference)) {
                        *result++ = {address, newValue.b1, oldValue.b1};
                        ResultsCount++;
                        _resultsInPool++;
                    }

                    address++;

                    if (DBM(newValue.b2, oldValue.b2, difference)) {
                        *result++ = {address, newValue.b2, oldValue.b2};
                        ResultsCount++;
                        _resultsInPool++;
                    }

                    address++;

                    if (DBM(newValue.b3, oldValue.b3, difference)) {
                        *result++ = {address, newValue.b3, oldValue.b3};
                        ResultsCount++;
                        _resultsInPool++;
                    }

                    address++;

                    if (DBM(newValue.b4, oldValue.b4, difference)) {
                        *result++ = {address, newValue.b4, oldValue.b4};
                        ResultsCount++;
                        _resultsInPool++;
                    }

                    address++;
                }

                break;
            }

            default: break;
        }

        _currentAddress = (address - _startRegion) / 4;
    }

    void Search32::SecondSearchUnknownU16(Storage<u32> &data, SearchFlags compare, Results32WithOld *result) {
        u32 address = _startRegion + _currentAddress * 4;

        switch (compare) {
            case SearchFlags::Equal: {
                for (u32 v : data) {
                    if (_resultsInPool > _maxResults - 2)
                        break;

                    Short32 oldValue = {v};
                    Short32 newValue = {*(u32*)address};

                    if (EQ(newValue.s1, oldValue.s1)) {
                        *result++ = {address, newValue.s1, oldValue.s1};
                        ResultsCount++;
                        _resultsInPool++;
                    }

                    address += 2;

                    if (EQ(newValue.s2, oldValue.s2)) {
                        *result++ = {address, newValue.s2, oldValue.s2};
                        ResultsCount++;
                        _resultsInPool++;
                    }

                    address += 2;
                }

                break;
            }

            case SearchFlags::NotEqual: {
                for (u32 v : data) {
                    if (_resultsInPool > _maxResults - 2)
                        break;

                    Short32 oldValue = {v};
                    Short32 newValue = {*(u32*)address};

                    if (NE(newValue.s1, oldValue.s1)) {
                        *result++ = {address, newValue.s1, oldValue.s1};
                        ResultsCount++;
                        _resultsInPool++;
                    }

                    address += 2;

                    if (NE(newValue.s2, oldValue.s2)) {
                        *result++ = {address, newValue.s2, oldValue.s2};
                        ResultsCount++;
                        _resultsInPool++;
                    }

                    address += 2;
                }

                break;
            }

            case SearchFlags::GreaterThan: {
                for (u32 v : data) {
                    if (_resultsInPool > _maxResults - 2)
                        break;

                    Short32 oldValue = {v};
                    Short32 newValue = {*(u32*)address};

                    if (GT(newValue.s1, oldValue.s1)) {
                        *result++ = {address, newValue.s1, oldValue.s1};
                        ResultsCount++;
                        _resultsInPool++;
                    }

                    address += 2;

                    if (GT(newValue.s2, oldValue.s2)) {
                        *result++ = {address, newValue.s2, oldValue.s2};
                        ResultsCount++;
                        _resultsInPool++;
                    }

                    address += 2;
                }

                break;
            }

            case SearchFlags::GreaterOrEqual: {
                for (u32 v : data) {
                    if (_resultsInPool > _maxResults - 2)
                        break;

                    Short32 oldValue = {v};
                    Short32 newValue = {*(u32*)address};

                    if (GE(newValue.s1, oldValue.s1)) {
                        *result++ = {address, newValue.s1, oldValue.s1};
                        ResultsCount++;
                        _resultsInPool++;
                    }

                    address += 2;

                    if (GE(newValue.s2, oldValue.s2)) {
                        *result++ = {address, newValue.s2, oldValue.s2};
                        ResultsCount++;
                        _resultsInPool++;
                    }

                    address += 2;
                }

                break;
            }

            case SearchFlags::LesserThan: {
                for (u32 v : data) {
                    if (_resultsInPool > _maxResults - 2)
                        break;

                    Short32 oldValue = {v};
                    Short32 newValue = {*(u32*)address};

                    if (LT(newValue.s1, oldValue.s1)) {
                        *result++ = {address, newValue.s1, oldValue.s1};
                        ResultsCount++;
                        _resultsInPool++;
                    }

                    address += 2;

                    if (LT(newValue.s2, oldValue.s2)) {
                        *result++ = {address, newValue.s2, oldValue.s2};
                        ResultsCount++;
                        _resultsInPool++;
                    }

                    address += 2;
                }

                break;
            }

            case SearchFlags::LesserOrEqual: {
                for (u32 v : data) {
                    if (_resultsInPool > _maxResults - 2)
                        break;

                    Short32 oldValue = {v};
                    Short32 newValue = {*(u32*)address};

                    if (LE(newValue.s1, oldValue.s1)) {
                        *result++ = {address, newValue.s1, oldValue.s1};
                        ResultsCount++;
                        _resultsInPool++;
                    }

                    address += 2;

                    if (LE(newValue.s2, oldValue.s2)) {
                        *result++ = {address, newValue.s2, oldValue.s2};
                        ResultsCount++;
                        _resultsInPool++;
                    }

                    address += 2;
                }

                break;
            }

            case SearchFlags::DifferentBy: {
                u16 difference = _checkValue.U16;

                for (u32 v : data) {
                    if (_resultsInPool > _maxResults - 2)
                        break;

                    Short32 oldValue = {v};
                    Short32 newValue = {*(u32*)address};

                    if (DB(newValue.s1, oldValue.s1, difference)) {
                        *result++ = {address, newValue.s1, oldValue.s1};
                        ResultsCount++;
                        _resultsInPool++;
                    }

                    address += 2;

                    if (DB(newValue.s2, oldValue.s2, difference)) {
                        *result++ = {address, newValue.s2, oldValue.s2};
                        ResultsCount++;
                        _resultsInPool++;
                    }

                    address += 2;
                }

                break;
            }

            case SearchFlags::DifferentByLess: {
                u16 difference = _checkValue.U16;

                for (u32 v : data) {
                    if (_resultsInPool > _maxResults - 2)
                        break;

                    Short32 oldValue = {v};
                    Short32 newValue = {*(u32*)address};

                    if (DBL(newValue.s1, oldValue.s1, difference)) {
                        *result++ = {address, newValue.s1, oldValue.s1};
                        ResultsCount++;
                        _resultsInPool++;
                    }

                    address += 2;

                    if (DBL(newValue.s2, oldValue.s2, difference)) {
                        *result++ = {address, newValue.s2, oldValue.s2};
                        ResultsCount++;
                        _resultsInPool++;
                    }

                    address += 2;
                }

                break;
            }

            case SearchFlags::DifferentByMore: {
                u16 difference = _checkValue.U16;

                for (u32 v : data) {
                    if (_resultsInPool > _maxResults - 2)
                        break;

                    Short32 oldValue = {v};
                    Short32 newValue = {*(u32*)address};

                    if (DBM(newValue.s1, oldValue.s1, difference)) {
                        *result++ = {address, newValue.s1, oldValue.s1};
                        ResultsCount++;
                        _resultsInPool++;
                    }

                    address += 2;

                    if (DBM(newValue.s2, oldValue.s2, difference)) {
                        *result++ = {address, newValue.s2, oldValue.s2};
                        ResultsCount++;
                        _resultsInPool++;
                    }

                    address += 2;
                }

                break;
            }

            default: break;
        }

        _currentAddress = (address - _startRegion) / 4;
    }

    void Search32::SecondSearchUnknownU32(Storage<u32> &data, SearchFlags compare, Results32WithOld *result) {
        u32 address = _startRegion + _currentAddress * 4;

        switch (compare) {
            case SearchFlags::Equal: {
                for (u32 value : data) {
                    if (_resultsInPool > _maxResults)
                        break;

                    u32 newValue = *(u32*)address;

                    if (EQ(newValue, value)) {
                        *result++ = {address, newValue, value};
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    address += 4;
                }

                break;
            }

            case SearchFlags::NotEqual: {
                for (u32 value : data) {
                    if (_resultsInPool > _maxResults)
                        break;

                    u32 newValue = *(u32*)address;

                    if (NE(newValue, value)) {
                        *result++ = {address, newValue, value};
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    address += 4;
                }

                break;
            }

            case SearchFlags::GreaterThan: {
                for (u32 value : data) {
                    if (_resultsInPool > _maxResults)
                        break;

                    u32 newValue = *(u32*)address;

                    if (GT(newValue, value)) {
                        *result++ = {address, newValue, value};
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    address += 4;
                }

                break;
            }

            case SearchFlags::GreaterOrEqual: {
                for (u32 value : data) {
                    if (_resultsInPool > _maxResults)
                        break;

                    u32 newValue = *(u32*)address;

                    if (GE(newValue, value)) {
                        *result++ = {address, newValue, value};
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    address += 4;
                }

                break;
            }

            case SearchFlags::LesserThan: {
                for (u32 value : data) {
                    if (_resultsInPool > _maxResults)
                        break;

                    u32 newValue = *(u32*)address;

                    if (LT(newValue, value)) {
                        *result++ = {address, newValue, value};
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    address += 4;
                }

                break;
            }

            case SearchFlags::LesserOrEqual: {
                for (u32 value : data) {
                    if (_resultsInPool > _maxResults)
                        break;

                    u32 newValue = *(u32*)address;

                    if (LE(newValue, value)) {
                        *result++ = {address, newValue, value};
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    address += 4;
                }

                break;
            }

            case SearchFlags::DifferentBy: {
                u32 difference = _checkValue.U32;

                for (u32 value : data) {
                    if (_resultsInPool > _maxResults)
                        break;

                    u32 newValue = *(u32*)address;

                    if (DB(newValue, value, difference)) {
                        *result++ = {address, newValue, value};
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    address += 4;
                }

                break;
            }

            case SearchFlags::DifferentByLess: {
                u32 difference = _checkValue.U32;

                for (u32 value : data) {
                    if (_resultsInPool > _maxResults)
                        break;

                    u32 newValue = *(u32*)address;

                    if (DBL(newValue, value, difference)) {
                        *result++ = {address, newValue, value};
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    address += 4;
                }

                break;
            }

            case SearchFlags::DifferentByMore: {
                u32 difference = _checkValue.U32;

                for (u32 value : data) {
                    if (_resultsInPool > _maxResults)
                        break;

                    u32 newValue = *(u32*)address;

                    if (DBM(newValue, value, difference)) {
                        *result++ = {address, newValue, value};
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    address += 4;
                }

                break;
            }

            default: break;
        }

        _currentAddress = (address - _startRegion) / 4;
    }

    void Search32::SecondSearchUnknownFloat(Storage<u32> &data, SearchFlags compare, Results32WithOld *result) {
        u32 address = _startRegion + _currentAddress * 4;

        switch (compare) {
            case SearchFlags::Equal: {
                for (u32 v : data) {
                    float value;
                    memcpy(&value, &v, sizeof(float));

                    if (_resultsInPool > _maxResults)
                        break;

                    float newValue = *(float*)address;

                    if (IsValid(value) && FP_EQ(newValue, value)) {
                        result->address = address;
                        result->newValue.Float = newValue;
                        result++->oldValue.Float = value;
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    address += 4;
                }

                break;
            }

            case SearchFlags::NotEqual: {
                for (u32 v : data) {
                    float value;
                    memcpy(&value, &v, sizeof(float));

                    if (_resultsInPool > _maxResults)
                        break;

                    float newValue = *(float*)address;

                    if (IsValid(value) && FP_NE(newValue, value)) {
                        result->address = address;
                        result->newValue.Float = newValue;
                        result++->oldValue.Float = value;
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    address += 4;
                }

                break;
            }

            case SearchFlags::GreaterThan: {
                for (u32 v : data) {
                    float value;
                    memcpy(&value, &v, sizeof(float));

                    if (_resultsInPool > _maxResults)
                        break;

                    float newValue = *(float*)address;

                    if (IsValid(value) && FP_GT(newValue, value)) {
                        result->address = address;
                        result->newValue.Float = newValue;
                        result++->oldValue.Float = value;
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    address += 4;
                }

                break;
            }

            case SearchFlags::GreaterOrEqual: {
                for (u32 v : data) {
                    float value;
                    memcpy(&value, &v, sizeof(float));

                    if (_resultsInPool > _maxResults)
                        break;

                    float newValue = *(float*)address;

                    if (IsValid(value) && FP_GE(newValue, value)) {
                        result->address = address;
                        result->newValue.Float = newValue;
                        result++->oldValue.Float = value;
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    address += 4;
                }

                break;
            }

            case SearchFlags::LesserThan: {
                for (u32 v : data) {
                    float value;
                    memcpy(&value, &v, sizeof(float));

                    if (_resultsInPool > _maxResults)
                        break;

                    float newValue = *(float*)address;

                    if (IsValid(value) && FP_LT(newValue, value)) {
                        result->address = address;
                        result->newValue.Float = newValue;
                        result++->oldValue.Float = value;
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    address += 4;
                }

                break;
            }

            case SearchFlags::LesserOrEqual: {
                for (u32 v : data) {
                    float value;
                    memcpy(&value, &v, sizeof(float));

                    if (_resultsInPool > _maxResults)
                        break;

                    float newValue = *(float*)address;

                    if (IsValid(value) && FP_LE(newValue, value)) {
                        result->address = address;
                        result->newValue.Float = newValue;
                        result++->oldValue.Float = value;
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    address += 4;
                }

                break;
            }

            case SearchFlags::DifferentBy: {
                float difference = _checkValue.Float;

                for (u32 v : data) {
                    float value;
                    memcpy(&value, &v, sizeof(float));

                    if (_resultsInPool > _maxResults)
                        break;

                    float newValue = *(float*)address;

                    if (IsValid(value) && FP_DB(newValue, value, difference)) {
                        result->address = address;
                        result->newValue.Float = newValue;
                        result++->oldValue.Float = value;
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    address += 4;
                }

                break;
            }

            case SearchFlags::DifferentByLess: {
                float difference = _checkValue.Float;

                for (u32 v : data) {
                    float value;
                    memcpy(&value, &v, sizeof(float));

                    if (_resultsInPool > _maxResults)
                        break;

                    float newValue = *(float*)address;

                    if (IsValid(value) && FP_DBL(newValue, value, difference)) {
                        result->address = address;
                        result->newValue.Float = newValue;
                        result++->oldValue.Float = value;
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    address += 4;
                }

                break;
            }

            case SearchFlags::DifferentByMore: {
                float difference = _checkValue.Float;

                for (u32 v : data) {
                    float value;
                    memcpy(&value, &v, sizeof(float));

                    if (_resultsInPool > _maxResults)
                        break;

                    float newValue = *(float*)address;

                    if (IsValid(value) && FP_DBM(newValue, value, difference)) {
                        result->address = address;
                        result->newValue.Float = newValue;
                        result++->oldValue.Float = value;
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    address += 4;
                }

                break;
            }

            default: break;
        }

        _currentAddress = (address - _startRegion) / 4;
    }

    void Search32::SubsidiarySearchSpecifiedU8(Storage<Results32WithOld> &data, SearchFlags compare, Results32WithOld *result) {
        u8 checkValue = _checkValue.U8;

        switch (compare) {
            case SearchFlags::Equal: {
                for (const Results32WithOld &res : data) {
                    if (_resultsInPool > _maxResults)
                        break;

                    u8 oldValue = res.newValue.U8;
                    u8 newValue = *(u8*)res.address;

                    if (EQ(newValue, checkValue)) {
                        *result++ = {res.address, newValue, oldValue};
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    _currentAddress++;
                }

                break;
            }

            case SearchFlags::NotEqual: {
                for (const Results32WithOld &res : data) {
                    if (_resultsInPool > _maxResults)
                        break;

                    u8 oldValue = res.newValue.U8;
                    u8 newValue = *(u8*)res.address;

                    if (NE(newValue, checkValue)) {
                        *result++ = {res.address, newValue, oldValue};
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    _currentAddress++;
                }

                break;
            }

            case SearchFlags::GreaterThan: {
                for (const Results32WithOld &res : data) {
                    if (_resultsInPool > _maxResults)
                        break;

                    u8 oldValue = res.newValue.U8;
                    u8 newValue = *(u8*)res.address;

                    if (GT(newValue, checkValue)) {
                        *result++ = {res.address, newValue, oldValue};
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    _currentAddress++;
                }

                break;
            }

            case SearchFlags::GreaterOrEqual: {
                for (const Results32WithOld &res : data) {
                    if (_resultsInPool > _maxResults)
                        break;

                    u8 oldValue = res.newValue.U8;
                    u8 newValue = *(u8*)res.address;

                    if (GE(newValue, checkValue)) {
                        *result++ = {res.address, newValue, oldValue};
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    _currentAddress++;
                }

                break;
            }

            case SearchFlags::LesserThan: {
                for (const Results32WithOld &res : data) {
                    if (_resultsInPool > _maxResults)
                        break;

                    u8 oldValue = res.newValue.U8;
                    u8 newValue = *(u8*)res.address;

                    if (LT(newValue, checkValue)) {
                        *result++ = {res.address, newValue, oldValue};
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    _currentAddress++;
                }

                break;
            }

            case SearchFlags::LesserOrEqual: {
                for (const Results32WithOld &res : data) {
                    if (_resultsInPool > _maxResults)
                        break;

                    u8 oldValue = res.newValue.U8;
                    u8 newValue = *(u8*)res.address;

                    if (LE(newValue, checkValue)) {
                        *result++ = {res.address, newValue, oldValue};
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    _currentAddress++;
                }

                break;
            }

            case SearchFlags::DifferentBy: {
                for (const Results32WithOld &res : data) {
                    if (_resultsInPool > _maxResults)
                        break;

                    u8 oldValue = res.newValue.U8;
                    u8 newValue = *(u8*)res.address;

                    if (DB(newValue, oldValue, checkValue)) {
                        *result++ = {res.address, newValue, oldValue};
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    _currentAddress++;
                }

                break;
            }

            case SearchFlags::DifferentByLess: {
                for (const Results32WithOld &res : data) {
                    if (_resultsInPool > _maxResults)
                        break;

                    u8 oldValue = res.newValue.U8;
                    u8 newValue = *(u8*)res.address;

                    if (DBL(newValue, oldValue, checkValue)) {
                        *result++ = {res.address, newValue, oldValue};
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    _currentAddress++;
                }

                break;
            }

            case SearchFlags::DifferentByMore: {
                for (const Results32WithOld &res : data) {
                    if (_resultsInPool > _maxResults)
                        break;

                    u8 oldValue = res.newValue.U8;
                    u8 newValue = *(u8*)res.address;

                    if (DBM(newValue, oldValue, checkValue)) {
                        *result++ = {res.address, newValue, oldValue};
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    _currentAddress++;
                }

                break;
            }

            default: break;
        }
    }

    void Search32::SubsidiarySearchSpecifiedU16(Storage<Results32WithOld> &data, SearchFlags compare, Results32WithOld *result) {
        u16 checkValue = _checkValue.U16;

        switch (compare) {
            case SearchFlags::Equal: {
                for (const Results32WithOld &res : data) {
                    if (_resultsInPool > _maxResults)
                        break;

                    u16 oldValue = res.newValue.U16;
                    u16 newValue = *(u16*)res.address;

                    if (EQ(newValue, checkValue)) {
                        *result++ = {res.address, newValue, oldValue};
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    _currentAddress++;
                }

                break;
            }

            case SearchFlags::NotEqual: {
                for (const Results32WithOld &res : data) {
                    if (_resultsInPool > _maxResults)
                        break;

                    u16 oldValue = res.newValue.U16;
                    u16 newValue = *(u16*)res.address;

                    if (NE(newValue, checkValue)) {
                        *result++ = {res.address, newValue, oldValue};
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    _currentAddress++;
                }

                break;
            }

            case SearchFlags::GreaterThan: {
                for (const Results32WithOld &res : data) {
                    if (_resultsInPool > _maxResults)
                        break;

                    u16 oldValue = res.newValue.U16;
                    u16 newValue = *(u16*)res.address;

                    if (GT(newValue, checkValue)) {
                        *result++ = {res.address, newValue, oldValue};
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    _currentAddress++;
                }

                break;
            }

            case SearchFlags::GreaterOrEqual: {
                for (const Results32WithOld &res : data) {
                    if (_resultsInPool > _maxResults)
                        break;

                    u16 oldValue = res.newValue.U16;
                    u16 newValue = *(u16*)res.address;

                    if (GE(newValue, checkValue)) {
                        *result++ = {res.address, newValue, oldValue};
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    _currentAddress++;
                }

                break;
            }

            case SearchFlags::LesserThan: {
                for (const Results32WithOld &res : data) {
                    if (_resultsInPool > _maxResults)
                        break;

                    u16 oldValue = res.newValue.U16;
                    u16 newValue = *(u16*)res.address;

                    if (LT(newValue, checkValue)) {
                        *result++ = {res.address, newValue, oldValue};
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    _currentAddress++;
                }

                break;
            }

            case SearchFlags::LesserOrEqual: {
                for (const Results32WithOld &res : data) {
                    if (_resultsInPool > _maxResults)
                        break;

                    u16 oldValue = res.newValue.U16;
                    u16 newValue = *(u16*)res.address;

                    if (LE(newValue, checkValue)) {
                        *result++ = {res.address, newValue, oldValue};
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    _currentAddress++;
                }

                break;
            }

            case SearchFlags::DifferentBy: {
                for (const Results32WithOld &res : data) {
                    if (_resultsInPool > _maxResults)
                        break;

                    u16 oldValue = res.newValue.U16;
                    u16 newValue = *(u16*)res.address;

                    if (DB(newValue, oldValue, checkValue)) {
                        *result++ = {res.address, newValue, oldValue};
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    _currentAddress++;
                }

                break;
            }

            case SearchFlags::DifferentByLess: {
                for (const Results32WithOld &res : data) {
                    if (_resultsInPool > _maxResults)
                        break;

                    u16 oldValue = res.newValue.U16;
                    u16 newValue = *(u16*)res.address;

                    if (DBL(newValue, oldValue, checkValue)) {
                        *result++ = {res.address, newValue, oldValue};
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    _currentAddress++;
                }

                break;
            }

            case SearchFlags::DifferentByMore: {
                for (const Results32WithOld &res : data) {
                    if (_resultsInPool > _maxResults)
                        break;

                    u16 oldValue = res.newValue.U16;
                    u16 newValue = *(u16*)res.address;

                    if (DBM(newValue, oldValue, checkValue)) {
                        *result++ = {res.address, newValue, oldValue};
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    _currentAddress++;
                }

                break;
            }

            default: break;
        }
    }

    void Search32::SubsidiarySearchSpecifiedU32(Storage<Results32WithOld> &data, SearchFlags compare, Results32WithOld *result) {
        u32 checkValue = _checkValue.U32;

        switch (compare) {
            case SearchFlags::Equal: {
                for (const Results32WithOld &res : data) {
                    if (_resultsInPool > _maxResults)
                        break;

                    u32 oldValue = res.newValue.U32;
                    u32 newValue = *(u32*)res.address;

                    if (EQ(newValue, checkValue)) {
                        *result++ = {res.address, newValue, oldValue};
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    _currentAddress++;
                }

                break;
            }

            case SearchFlags::NotEqual: {
                for (const Results32WithOld &res : data) {
                    if (_resultsInPool > _maxResults)
                        break;

                    u32 oldValue = res.newValue.U32;
                    u32 newValue = *(u32*)res.address;

                    if (NE(newValue, checkValue)) {
                        *result++ = {res.address, newValue, oldValue};
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    _currentAddress++;
                }

                break;
            }

            case SearchFlags::GreaterThan: {
                for (const Results32WithOld &res : data) {
                    if (_resultsInPool > _maxResults)
                        break;

                    u32 oldValue = res.newValue.U32;
                    u32 newValue = *(u32*)res.address;

                    if (GT(newValue, checkValue)) {
                        *result++ = {res.address, newValue, oldValue};
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    _currentAddress++;
                }

                break;
            }

            case SearchFlags::GreaterOrEqual: {
                for (const Results32WithOld &res : data) {
                    if (_resultsInPool > _maxResults)
                        break;

                    u32 oldValue = res.newValue.U32;
                    u32 newValue = *(u32*)res.address;

                    if (GE(newValue, checkValue)) {
                        *result++ = {res.address, newValue, oldValue};
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    _currentAddress++;
                }

                break;
            }

            case SearchFlags::LesserThan: {
                for (const Results32WithOld &res : data) {
                    if (_resultsInPool > _maxResults)
                        break;

                    u32 oldValue = res.newValue.U32;
                    u32 newValue = *(u32*)res.address;

                    if (LT(newValue, checkValue)) {
                        *result++ = {res.address, newValue, oldValue};
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    _currentAddress++;
                }

                break;
            }

            case SearchFlags::LesserOrEqual: {
                for (const Results32WithOld &res : data) {
                    if (_resultsInPool > _maxResults)
                        break;

                    u32 oldValue = res.newValue.U32;
                    u32 newValue = *(u32*)res.address;

                    if (LE(newValue, checkValue)) {
                        *result++ = {res.address, newValue, oldValue};
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    _currentAddress++;
                }

                break;
            }

            case SearchFlags::DifferentBy: {
                for (const Results32WithOld &res : data) {
                    if (_resultsInPool > _maxResults)
                        break;

                    u32 oldValue = res.newValue.U32;
                    u32 newValue = *(u32*)res.address;

                    if (DB(newValue, oldValue, checkValue)) {
                        *result++ = {res.address, newValue, oldValue};
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    _currentAddress++;
                }

                break;
            }

            case SearchFlags::DifferentByLess: {
                for (const Results32WithOld &res : data) {
                    if (_resultsInPool > _maxResults)
                        break;

                    u32 oldValue = res.newValue.U32;
                    u32 newValue = *(u32*)res.address;

                    if (DBL(newValue, oldValue, checkValue)) {
                        *result++ = {res.address, newValue, oldValue};
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    _currentAddress++;
                }

                break;
            }

            case SearchFlags::DifferentByMore: {
                for (const Results32WithOld &res : data) {
                    if (_resultsInPool > _maxResults)
                        break;

                    u32 oldValue = res.newValue.U32;
                    u32 newValue = *(u32*)res.address;

                    if (DBM(newValue, oldValue, checkValue)) {
                        *result++ = {res.address, newValue, oldValue};
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    _currentAddress++;
                }

                break;
            }

            default: break;
        }
    }

    void Search32::SubsidiarySearchSpecifiedFloat(Storage<Results32WithOld> &data, SearchFlags compare, Results32WithOld *result) {
        float checkValue = _checkValue.Float;

        switch (compare) {
            case SearchFlags::Equal: {
                for (const Results32WithOld &res : data) {
                    if (_resultsInPool > _maxResults)
                        break;

                    float oldValue = res.newValue.Float;
                    float newValue = *(float*)res.address;

                    if (FP_EQ(newValue, checkValue)) {
                        result->address = res.address;
                        result->newValue.Float = newValue;
                        result++->oldValue.Float = oldValue;
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    _currentAddress++;
                }

                break;
            }

            case SearchFlags::NotEqual: {
                for (const Results32WithOld &res : data) {
                    if (_resultsInPool > _maxResults)
                        break;

                    float oldValue = res.newValue.Float;
                    float newValue = *(float*)res.address;

                    if (FP_NE(newValue, checkValue)) {
                        result->address = res.address;
                        result->newValue.Float = newValue;
                        result++->oldValue.Float = oldValue;
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    _currentAddress++;
                }

                break;
            }

            case SearchFlags::GreaterThan: {
                for (const Results32WithOld &res : data) {
                    if (_resultsInPool > _maxResults)
                        break;

                    float oldValue = res.newValue.Float;
                    float newValue = *(float*)res.address;

                    if (FP_GT(newValue, checkValue)) {
                        result->address = res.address;
                        result->newValue.Float = newValue;
                        result++->oldValue.Float = oldValue;
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    _currentAddress++;
                }

                break;
            }

            case SearchFlags::GreaterOrEqual: {
                for (const Results32WithOld &res : data) {
                    if (_resultsInPool > _maxResults)
                        break;

                    float oldValue = res.newValue.Float;
                    float newValue = *(float*)res.address;

                    if (FP_GE(newValue, checkValue)) {
                        result->address = res.address;
                        result->newValue.Float = newValue;
                        result++->oldValue.Float = oldValue;
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    _currentAddress++;
                }

                break;
            }

            case SearchFlags::LesserThan: {
                for (const Results32WithOld &res : data) {
                    if (_resultsInPool > _maxResults)
                        break;

                    float oldValue = res.newValue.Float;
                    float newValue = *(float*)res.address;

                    if (FP_LT(newValue, checkValue)) {
                        result->address = res.address;
                        result->newValue.Float = newValue;
                        result++->oldValue.Float = oldValue;
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    _currentAddress++;
                }

                break;
            }

            case SearchFlags::LesserOrEqual: {
                for (const Results32WithOld &res : data) {
                    if (_resultsInPool > _maxResults)
                        break;

                    float oldValue = res.newValue.Float;
                    float newValue = *(float*)res.address;

                    if (FP_LE(newValue, checkValue)) {
                        result->address = res.address;
                        result->newValue.Float = newValue;
                        result++->oldValue.Float = oldValue;
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    _currentAddress++;
                }

                break;
            }

            case SearchFlags::DifferentBy: {
                for (const Results32WithOld &res : data) {
                    if (_resultsInPool > _maxResults)
                        break;

                    float oldValue = res.newValue.Float;
                    float newValue = *(float*)res.address;

                    if (FP_DB(newValue, oldValue, checkValue)) {
                        result->address = res.address;
                        result->newValue.Float = newValue;
                        result++->oldValue.Float = oldValue;
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    _currentAddress++;
                }

                break;
            }

            case SearchFlags::DifferentByLess: {
                for (const Results32WithOld &res : data) {
                    if (_resultsInPool > _maxResults)
                        break;

                    float oldValue = res.newValue.Float;
                    float newValue = *(float*)res.address;

                    if (FP_DBL(newValue, oldValue, checkValue)) {
                        result->address = res.address;
                        result->newValue.Float = newValue;
                        result++->oldValue.Float = oldValue;
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    _currentAddress++;
                }

                break;
            }

            case SearchFlags::DifferentByMore: {
                for (const Results32WithOld &res : data) {
                    if (_resultsInPool > _maxResults)
                        break;

                    float oldValue = res.newValue.Float;
                    float newValue = *(float*)res.address;

                    if (FP_DBM(newValue, oldValue, checkValue)) {
                        result->address = res.address;
                        result->newValue.Float = newValue;
                        result++->oldValue.Float = oldValue;
                        _resultsInPool++;
                        ResultsCount++;
                    }

                    _currentAddress++;
                }

                break;
            }

            default: break;
        }
    }

    void Search32::SubsidiarySearchUnknownU8(Storage<Results32WithOld> &data, SearchFlags compare, Results32WithOld *result) {
        if (IsSpecifiedSearch(_flags)) {
            switch (compare) {
                case SearchFlags::Equal: {
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u8 oldValue = res.newValue.U8;
                        u8 newValue = *(u8*)res.address;

                        if (EQ(newValue, oldValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::NotEqual: {
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u8 oldValue = res.newValue.U8;
                        u8 newValue = *(u8*)res.address;

                        if (NE(newValue, oldValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::GreaterThan: {
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u8 oldValue = res.newValue.U8;
                        u8 newValue = *(u8*)res.address;

                        if (GT(newValue, oldValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::GreaterOrEqual: {
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u8 oldValue = res.newValue.U8;
                        u8 newValue = *(u8*)res.address;

                        if (GE(newValue, oldValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::LesserThan: {
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u8 oldValue = res.newValue.U8;
                        u8 newValue = *(u8*)res.address;

                        if (LT(newValue, oldValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::LesserOrEqual: {
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u8 oldValue = res.newValue.U8;
                        u8 newValue = *(u8*)res.address;

                        if (LE(newValue, oldValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::DifferentBy: {
                    u8 checkValue = _checkValue.U8;
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u8 oldValue = res.newValue.U8;
                        u8 newValue = *(u8*)res.address;

                        if (DB(newValue, oldValue, checkValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::DifferentByLess: {
                    u8 checkValue = _checkValue.U8;
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u8 oldValue = res.newValue.U8;
                        u8 newValue = *(u8*)res.address;

                        if (DBL(newValue, oldValue, checkValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::DifferentByMore: {
                    u8 checkValue = _checkValue.U8;
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u8 oldValue = res.newValue.U8;
                        u8 newValue = *(u8*)res.address;

                        if (DBM(newValue, oldValue, checkValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                default: break;
            }
        }

        // Else for unknown search
        else {
            switch (compare) {
                case SearchFlags::Equal: {
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u8 oldValue = res.newValue.U8;
                        u8 newValue = *(u8*)res.address;

                        if (EQ(newValue, oldValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::NotEqual: {
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u8 oldValue = res.newValue.U8;
                        u8 newValue = *(u8*)res.address;

                        if (NE(newValue, oldValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::GreaterThan: {
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u8 oldValue = res.newValue.U8;
                        u8 newValue = *(u8*)res.address;

                        if (GT(newValue, oldValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::GreaterOrEqual: {
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u8 oldValue = res.newValue.U8;
                        u8 newValue = *(u8*)res.address;

                        if (GE(newValue, oldValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::LesserThan: {
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u8 oldValue = res.newValue.U8;
                        u8 newValue = *(u8*)res.address;

                        if (LT(newValue, oldValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::LesserOrEqual: {
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u8 oldValue = res.newValue.U8;
                        u8 newValue = *(u8*)res.address;

                        if (LE(newValue, oldValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::DifferentBy: {
                    u8 checkValue = _checkValue.U8;
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u8 oldValue = res.newValue.U8;
                        u8 newValue = *(u8*)res.address;

                        if (DB(newValue, oldValue, checkValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::DifferentByLess: {
                    u8 checkValue = _checkValue.U8;
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u8 oldValue = res.newValue.U8;
                        u8 newValue = *(u8*)res.address;

                        if (DBL(newValue, oldValue, checkValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::DifferentByMore: {
                    u8 checkValue = _checkValue.U8;
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u8 oldValue = res.newValue.U8;
                        u8 newValue = *(u8*)res.address;

                        if (DBM(newValue, oldValue, checkValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                default: break;
            }
        }
    }

    void Search32::SubsidiarySearchUnknownU16(Storage<Results32WithOld> &data, SearchFlags compare, Results32WithOld *result) {
        u16 checkValue = _checkValue.U16;

        if (IsSpecifiedSearch(_flags)) {
            switch (compare) {
                case SearchFlags::Equal: {
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u16 oldValue = res.newValue.U16;
                        u16 newValue = *(u16*)res.address;

                        if (EQ(newValue, oldValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::NotEqual: {
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u16 oldValue = res.newValue.U16;
                        u16 newValue = *(u16*)res.address;

                        if (NE(newValue, oldValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::GreaterThan: {
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u16 oldValue = res.newValue.U16;
                        u16 newValue = *(u16*)res.address;

                        if (GT(newValue, oldValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::GreaterOrEqual: {
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u16 oldValue = res.newValue.U16;
                        u16 newValue = *(u16*)res.address;

                        if (GE(newValue, oldValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::LesserThan: {
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u16 oldValue = res.newValue.U16;
                        u16 newValue = *(u16*)res.address;

                        if (LT(newValue, oldValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::LesserOrEqual: {
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u16 oldValue = res.newValue.U16;
                        u16 newValue = *(u16*)res.address;

                        if (LE(newValue, oldValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::DifferentBy: {
                    u16 checkValue = _checkValue.U16;
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u16 oldValue = res.newValue.U16;
                        u16 newValue = *(u16*)res.address;

                        if (DB(newValue, oldValue, checkValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::DifferentByLess: {
                    u16 checkValue = _checkValue.U16;
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u16 oldValue = res.newValue.U16;
                        u16 newValue = *(u16*)res.address;

                        if (DBL(newValue, oldValue, checkValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::DifferentByMore: {
                    u16 checkValue = _checkValue.U16;
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u16 oldValue = res.newValue.U16;
                        u16 newValue = *(u16*)res.address;

                        if (DBM(newValue, oldValue, checkValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                default: break;
            }
        }

        // Else for unknown search
        else {
            switch (compare) {
                case SearchFlags::Equal: {
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u16 oldValue = res.newValue.U16;
                        u16 newValue = *(u16*)res.address;

                        if (EQ(newValue, oldValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::NotEqual: {
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u16 oldValue = res.newValue.U16;
                        u16 newValue = *(u16*)res.address;

                        if (NE(newValue, oldValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::GreaterThan: {
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u16 oldValue = res.newValue.U16;
                        u16 newValue = *(u16*)res.address;

                        if (GT(newValue, oldValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::GreaterOrEqual: {
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u16 oldValue = res.newValue.U16;
                        u16 newValue = *(u16*)res.address;

                        if (GE(newValue, oldValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::LesserThan: {
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u16 oldValue = res.newValue.U16;
                        u16 newValue = *(u16*)res.address;

                        if (LT(newValue, oldValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::LesserOrEqual: {
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u16 oldValue = res.newValue.U16;
                        u16 newValue = *(u16*)res.address;

                        if (LE(newValue, oldValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::DifferentBy: {
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u16 oldValue = res.newValue.U16;
                        u16 newValue = *(u16*)res.address;

                        if (DB(newValue, oldValue, checkValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::DifferentByLess: {
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u16 oldValue = res.newValue.U16;
                        u16 newValue = *(u16*)res.address;

                        if (DBL(newValue, oldValue, checkValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::DifferentByMore: {
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u16 oldValue = res.newValue.U16;
                        u16 newValue = *(u16*)res.address;

                        if (DBM(newValue, oldValue, checkValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                default: break;
            }
        }
    }

    void Search32::SubsidiarySearchUnknownU32(Storage<Results32WithOld> &data, SearchFlags compare, Results32WithOld *result) {
        if (IsSpecifiedSearch(_flags)) {
            switch (compare) {
                case SearchFlags::Equal: {
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u32 oldValue = res.newValue.U32;
                        u32 newValue = *(u32*)res.address;

                        if (EQ(newValue, oldValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::NotEqual: {
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u32 oldValue = res.newValue.U32;
                        u32 newValue = *(u32*)res.address;

                        if (NE(newValue, oldValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::GreaterThan: {
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u32 oldValue = res.newValue.U32;
                        u32 newValue = *(u32*)res.address;

                        if (GT(newValue, oldValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::GreaterOrEqual: {
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u32 oldValue = res.newValue.U32;
                        u32 newValue = *(u32*)res.address;

                        if (GE(newValue, oldValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::LesserThan: {
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u32 oldValue = res.newValue.U32;
                        u32 newValue = *(u32*)res.address;

                        if (LT(newValue, oldValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::LesserOrEqual: {
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u32 oldValue = res.newValue.U32;
                        u32 newValue = *(u32*)res.address;

                        if (LE(newValue, oldValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::DifferentBy: {
                    u32 checkValue = _checkValue.U32;
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u32 oldValue = res.newValue.U32;
                        u32 newValue = *(u32*)res.address;

                        if (DB(newValue, oldValue, checkValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::DifferentByLess: {
                    u32 checkValue = _checkValue.U32;
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u32 oldValue = res.newValue.U32;
                        u32 newValue = *(u32*)res.address;

                        if (DBL(newValue, oldValue, checkValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::DifferentByMore: {
                    u32 checkValue = _checkValue.U32;
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u32 oldValue = res.newValue.U32;
                        u32 newValue = *(u32*)res.address;

                        if (DBM(newValue, oldValue, checkValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                default: break;
            }
        }

        // Else for unknown search
        else {
            switch (compare) {
                case SearchFlags::Equal: {
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u32 oldValue = res.newValue.U32;
                        u32 newValue = *(u32*)res.address;

                        if (EQ(newValue, oldValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::NotEqual: {
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u32 oldValue = res.newValue.U32;
                        u32 newValue = *(u32*)res.address;

                        if (NE(newValue, oldValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::GreaterThan: {
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u32 oldValue = res.newValue.U32;
                        u32 newValue = *(u32*)res.address;

                        if (GT(newValue, oldValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::GreaterOrEqual: {
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u32 oldValue = res.newValue.U32;
                        u32 newValue = *(u32*)res.address;

                        if (GE(newValue, oldValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::LesserThan: {
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u32 oldValue = res.newValue.U32;
                        u32 newValue = *(u32*)res.address;

                        if (LT(newValue, oldValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::LesserOrEqual: {
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u32 oldValue = res.newValue.U32;
                        u32 newValue = *(u32*)res.address;

                        if (LE(newValue, oldValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::DifferentBy: {
                    u32 checkValue = _checkValue.U32;
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u32 oldValue = res.newValue.U32;
                        u32 newValue = *(u32*)res.address;

                        if (DB(newValue, oldValue, checkValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::DifferentByLess: {
                    u32 checkValue = _checkValue.U32;
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u32 oldValue = res.newValue.U32;
                        u32 newValue = *(u32*)res.address;

                        if (DBL(newValue, oldValue, checkValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::DifferentByMore: {
                    u32 checkValue = _checkValue.U32;
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        u32 oldValue = res.newValue.U32;
                        u32 newValue = *(u32*)res.address;

                        if (DBM(newValue, oldValue, checkValue)) {
                            *result++ = {res.address, newValue, oldValue};
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                default: break;
            }
        }
    }

    void Search32::SubsidiarySearchUnknownFloat(Storage<Results32WithOld> &data, SearchFlags compare, Results32WithOld *result) {
        float checkValue = _checkValue.Float;

        // If current search is specified
        if (IsSpecifiedSearch(_flags)) {
            switch (compare) {
                case SearchFlags::Equal: {
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        float oldValue = res.newValue.Float;
                        float newValue = *(float*)res.address;

                        if (FP_EQ(newValue, checkValue)) {
                            result->address = res.address;
                            result->newValue.Float = newValue;
                            result++->oldValue.Float = oldValue;
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::NotEqual: {
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        float oldValue = res.newValue.Float;
                        float newValue = *(float*)res.address;

                        if (FP_NE(newValue, checkValue)) {
                            result->address = res.address;
                            result->newValue.Float = newValue;
                            result++->oldValue.Float = oldValue;
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::GreaterThan: {
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        float oldValue = res.newValue.Float;
                        float newValue = *(float*)res.address;

                        if (FP_GT(newValue, checkValue)) {
                            result->address = res.address;
                            result->newValue.Float = newValue;
                            result++->oldValue.Float = oldValue;
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::GreaterOrEqual: {
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        float oldValue = res.newValue.Float;
                        float newValue = *(float*)res.address;

                        if (FP_GE(newValue, checkValue)) {
                            result->address = res.address;
                            result->newValue.Float = newValue;
                            result++->oldValue.Float = oldValue;
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::LesserThan: {
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        float oldValue = res.newValue.Float;
                        float newValue = *(float*)res.address;

                        if (FP_LT(newValue, checkValue)) {
                            result->address = res.address;
                            result->newValue.Float = newValue;
                            result++->oldValue.Float = oldValue;
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::LesserOrEqual: {
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        float oldValue = res.newValue.Float;
                        float newValue = *(float*)res.address;

                        if (FP_LE(newValue, checkValue)) {
                            result->address = res.address;
                            result->newValue.Float = newValue;
                            result++->oldValue.Float = oldValue;
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::DifferentBy: {
                    float checkValue = _checkValue.Float;
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        float oldValue = res.newValue.Float;
                        float newValue = *(float*)res.address;

                        if (FP_DB(newValue, oldValue, checkValue)) {
                            result->address = res.address;
                            result->newValue.Float = newValue;
                            result++->oldValue.Float = oldValue;
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::DifferentByLess: {
                    float checkValue = _checkValue.Float;
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        float oldValue = res.newValue.Float;
                        float newValue = *(float*)res.address;

                        if (FP_DBL(newValue, oldValue, checkValue)) {
                            result->address = res.address;
                            result->newValue.Float = newValue;
                            result++->oldValue.Float = oldValue;
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::DifferentByMore: {
                    float checkValue = _checkValue.Float;
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        float oldValue = res.newValue.Float;
                        float newValue = *(float*)res.address;

                        if (FP_DBM(newValue, oldValue, checkValue)) {
                            result->address = res.address;
                            result->newValue.Float = newValue;
                            result++->oldValue.Float = oldValue;
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                default: break;
            }
        }

        // Else for unknown search
        else {
            switch (compare) {
                case SearchFlags::Equal: {
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        float oldValue = res.newValue.Float;
                        float newValue = *(float*)res.address;

                        if (FP_EQ(newValue, oldValue)) {
                            result->address = res.address;
                            result->newValue.Float = newValue;
                            result++->oldValue.Float = oldValue;
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::NotEqual: {
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        float oldValue = res.newValue.Float;
                        float newValue = *(float*)res.address;

                        if (FP_NE(newValue, oldValue)) {
                            result->address = res.address;
                            result->newValue.Float = newValue;
                            result++->oldValue.Float = oldValue;
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::GreaterThan: {
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        float oldValue = res.newValue.Float;
                        float newValue = *(float*)res.address;

                        if (FP_GT(newValue, oldValue)) {
                            result->address = res.address;
                            result->newValue.Float = newValue;
                            result++->oldValue.Float = oldValue;
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::GreaterOrEqual: {
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        float oldValue = res.newValue.Float;
                        float newValue = *(float*)res.address;

                        if (FP_GE(newValue, oldValue)) {
                            result->address = res.address;
                            result->newValue.Float = newValue;
                            result++->oldValue.Float = oldValue;
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::LesserThan: {
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        float oldValue = res.newValue.Float;
                        float newValue = *(float*)res.address;

                        if (FP_LT(newValue, oldValue)) {
                            result->address = res.address;
                            result->newValue.Float = newValue;
                            result++->oldValue.Float = oldValue;
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::LesserOrEqual: {
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        float oldValue = res.newValue.Float;
                        float newValue = *(float*)res.address;

                        if (FP_LE(newValue, oldValue)) {
                            result->address = res.address;
                            result->newValue.Float = newValue;
                            result++->oldValue.Float = oldValue;
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::DifferentBy: {
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        float oldValue = res.newValue.Float;
                        float newValue = *(float*)res.address;

                        if (FP_DB(newValue, oldValue, checkValue)) {
                            result->address = res.address;
                            result->newValue.Float = newValue;
                            result++->oldValue.Float = oldValue;
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::DifferentByLess: {
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        float oldValue = res.newValue.Float;
                        float newValue = *(float*)res.address;

                        if (FP_DBL(newValue, oldValue, checkValue)) {
                            result->address = res.address;
                            result->newValue.Float = newValue;
                            result++->oldValue.Float = oldValue;
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                case SearchFlags::DifferentByMore: {
                    for (const Results32WithOld &res : data) {
                        if (_resultsInPool > _maxResults)
                            break;

                        float oldValue = res.newValue.Float;
                        float newValue = *(float*)res.address;

                        if (FP_DBM(newValue, oldValue, checkValue)) {
                            result->address = res.address;
                            result->newValue.Float = newValue;
                            result++->oldValue.Float = oldValue;
                            _resultsInPool++;
                            ResultsCount++;
                        }

                        _currentAddress++;
                    }

                    break;
                }

                default: break;
            }
        }
    }
}