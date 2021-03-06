/************************************************************************
 * Copyright(c) 2020, One Unified. All rights reserved.                 *
 * email: info@oneunified.net                                           *
 *                                                                      *
 * This file is provided as is WITHOUT ANY WARRANTY                     *
 *  without even the implied warranty of                                *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                *
 *                                                                      *
 * This software may not be used nor distributed without proper license *
 * agreement.                                                           *
 *                                                                      *
 * See the file LICENSE.txt for redistribution information.             *
 ************************************************************************/

/*
 * File:    Collar.h
 * Author:  raymond@burkholder.net
 * Project: TFOptionCombos
 * Created on July 19, 2020, 05:43 PM
 */

#ifndef COLLAR_H
#define COLLAR_H

#include <TFTrading/MonitorOrder.h>

#include "Combo.h"
#include "Tracker.h"

namespace ou { // One Unified
namespace tf { // TradeFrame
namespace option { // options

class Collar: public Combo {
public:

  Collar();
  Collar( const Collar& rhs );
  Collar& operator=( const Collar& rhs ) = delete;
  Collar( const Collar&& rhs );
  virtual ~Collar();

  static size_t LegCount();

  static void ChooseLegs( // throw Chain exceptions
    Combo::E20DayDirection direction,
    const mapChains_t& chains,
    boost::gregorian::date,
    double priceUnderlying,
    fLegSelected_t&& );

  static const std::string Name( const std::string& sUnderlying, const mapChains_t& chains, boost::gregorian::date date, double price, Combo::E20DayDirection );

  virtual void Tick( double dblUnderlyingSlope, double dblPriceUnderlying, ptime dt );

  // long by default for entry, short doesn't make much sense due to combo type
  virtual void PlaceOrder( ou::tf::OrderSide::enumOrderSide );
  virtual void PlaceOrder( size_t ix, ou::tf::OrderSide::enumOrderSide );

  virtual double GetNet( double price );

protected:
  virtual void Init( boost::gregorian::date, const mapChains_t* );
private:

  Tracker m_trackerFront;
  Tracker m_trackerSynthetic;

  ou::tf::MonitorOrder m_monitor;  // used for closing

};

} // namespace option
} // namespace tf
} // namespace ou

#endif /* COLLAR_H */
