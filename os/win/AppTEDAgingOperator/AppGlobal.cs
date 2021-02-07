using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Operator = libTESys.AutoGen.Control.Operator;

namespace AppTEDAgingOperator
{
    public class AppGlobal
    {
        static private AppGlobal _Inst;

        static public void Init()
        {
            _Inst = new AppGlobal();
        }

        static public AppGlobal Inst
        {
            get { return _Inst;  }
        }

        private Operator _Operator;

        private AppGlobal()
        {
            _Operator = new Operator();
        }
                
        public Operator Operator
        {
            get
            {
                return _Operator;
            }
        }

        
    }
}

