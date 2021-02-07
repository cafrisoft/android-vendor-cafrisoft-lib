using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using libTESys.AutoGen.Native;

namespace libTESys.AutoGen.DLL
{
    public class Base
    {
        private const string _ROOTPATH = @"."; // string.Empty;
        private static string _DLLNAME = "AnapassTESysModule";

        public static string DLLNAME
        {
            get
            {
                return _DLLNAME;
            }
        }

        public static IntPtr LoadLibrary()
        {
            //var dependencies = LibraryDependenciesMap[libraryName];
            //dependencies.ForEach(x => GetOrLoadLibrary(x));
            var version = 1;// LibraryVersionMap[libraryName];
            var ptr = LibraryLoader.LoadNativeLibrary(Base._ROOTPATH, Base._DLLNAME, version);
            if (ptr == IntPtr.Zero)
            {
                throw new DllNotFoundException($"Unable to load DLL '{Base._DLLNAME}.dll': The specified module could not be found."
                    + "\n " + StringLib.TESysModuelLoadFail
                    );
            }
            return ptr;
        }

    }
}
