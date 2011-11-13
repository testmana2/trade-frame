/************************************************************************
 * Copyright(c) 2011, One Unified. All rights reserved.                 *
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

#pragma once

#include <string>

#include <TFTimeSeries/TimeSeries.h>
#include <TFTimeSeries/BarFactory.h>

#include <TFIndicators/TSSWStats.h>

#include <TFSimulation/SimulationProvider.h>

#include <TFTrading/PortfolioManager.h>
#include <TFTrading/ProviderManager.h>
#include <TFTrading/Position.h>
#include <TFTrading/Instrument.h>

#include <OUCharting/ChartDataView.h>
#include <OUCharting/ChartEntryBars.h>
#include <OUCharting/ChartEntryVolume.h>
#include <OUCharting/ChartEntryIndicator.h>

class Strategy
{
public:

  Strategy(void);
  ~Strategy(void);

  void Start( const std::string& sSymbolPath );

  ou::ChartDataView& GetChartDataView( void ) {return m_dvChart; };

protected:
private:

  enum stateTrade {
    ETradeOut, ETradeLong, ETradeShort, ETradeDone
  } m_stateTrade;

  std::stringstream m_ss;

  typedef ou::tf::CPosition::pPosition_t pPosition_t;
  typedef ou::tf::CInstrument::pInstrument_t pInstrument_t;
  typedef ou::tf::CProviderInterfaceBase::pProvider_t pProvider_t;
  typedef ou::tf::CSimulationProvider::pProvider_t pProviderSim_t;

  typedef ou::tf::CInstrument::pInstrument_t m_pInstrument_t;
  pInstrument_t m_pShortInstrument;
  pInstrument_t m_pLongInstrument;
  pInstrument_t m_pTestInstrument;

  ou::tf::CQuotes m_quotes;
  ou::tf::CTrades m_trades;
  ou::tf::CBars m_bars;

  ou::tf::CBarFactory m_barFactory;

  typedef ou::ChartEntryBase::pChartEntryBase_t pChartEntryBase_t;
  ou::ChartDataView m_dvChart;
  ou::ChartEntryBars m_ceBars;
  ou::ChartEntryVolume m_ceVolume;
  ou::ChartEntryIndicator m_ceSlope;

  typedef ou::tf::CSimulationProvider::pSymbol_t pSimSymbol_t;

  ou::tf::CPosition::pPosition_t pPosition;

  ptime m_dtEnd;
  unsigned int m_nTransitions;

  ou::tf::TSSWStatsMidQuote m_sma1min;
  ou::tf::TSSWStatsMidQuote m_sma2min;
  ou::tf::TSSWStatsMidQuote m_sma3min;
  ou::tf::TSSWStatsMidQuote m_sma5min;
  ou::tf::TSSWStatsMidQuote m_sma15min;

  pProviderSim_t m_sim;
  bool m_bSimConnected;

  pProvider_t m_pExecutionProvider;
  pProvider_t m_pDataProvider;

  void HandleSimulatorConnected( int );
  void HandleSimulatorDisConnected( int );

  void HandleOnExecConnected( int ); 
  void HandleOnExecDisconnected( int );

  void HandleOnData1Connected( int );
  void HandleOnData1Disconnected( int );

  void HandleQuote( const ou::tf::CQuote& quote );
  void HandleTrade( const ou::tf::CTrade& trade );
  void HandleSimulationComplete( void );

  void HandleExecution( ou::tf::CPosition::execution_delegate_t del );
  void HandleCommission( const ou::tf::CPosition* pPosition );

  void HandleBarCompletion( const ou::tf::CBar& );
};
