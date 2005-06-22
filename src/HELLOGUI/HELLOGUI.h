//  HELLOGUI : HELLO component GUI implemetation 
//

#ifndef _HELLOGUI_H_
#define _HELLOGUI_H_

#include <SalomeApp_Module.h>

#include <SALOMEconfig.h>
#include CORBA_CLIENT_HEADER(HELLO_Gen)

class SalomeApp_Application;
class HELLOGUI: public SalomeApp_Module
{
  Q_OBJECT

public:
  HELLOGUI();

  void    initialize( CAM_Application* );
  QString engineIOR() const;
  void    windows( QMap<int, int>& ) const;

  static HELLO_ORB::HELLO_Gen_ptr InitHELLOGen( SalomeApp_Application* );

public slots:
  bool    deactivateModule( SUIT_Study* );
  bool    activateModule( SUIT_Study* );

protected slots:
  void            OnMyNewItem();
  void            OnGetBanner();
};

#endif
