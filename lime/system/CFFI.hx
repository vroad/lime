package lime.system; #if !macro


#if sys
import sys.io.Process;
#end


class CFFI {
	
	
	@:noCompletion private static var __moduleNames:Map<String, String> = null;
	
	#if neko
	private static var __loadedNekoAPI:Bool;
	#elseif nodejs
	private static var __nodeNDLLModule:Dynamic;
	#end
	
	public static var available:Bool;
	public static var enabled:Bool;
	
	
	private static function __init__ ():Void {
		
		#if (cpp || neko || nodejs)
		available = true;
		enabled = #if disable_cffi false; #else true; #end
		#else
		available = false;
		enabled = false;
		#end
		
	}
	
	
	/**
	 * Tries to load a native CFFI primitive on compatible platforms
	 * @param	library	The name of the native library (such as "lime")
	 * @param	method	The exported primitive method name
	 * @param	args	The number of arguments
	 * @param	lazy	Whether to load the symbol immediately, or to allow lazy loading
	 * @return	The loaded method
	 */
	public static function load (library:String, method:String, args:Int = 0, lazy:Bool = false):Dynamic {
		
		#if (disable_cffi || macro)
		var enabled = false;
		#end
		
		#if optional_cffi
		if (library != "lime" || method != "neko_init") {
			
			lazy = true;
			
		}
		#end
		
		if (!enabled) {
			
			return Reflect.makeVarArgs (function (__) return {});
			
		}
		
		var result:Dynamic = null;
		
		#if (!disable_cffi && !macro)
		#if (sys && !html5)
		
		if (__moduleNames == null) __moduleNames = new Map<String, String> ();
		
		if (lazy) {
			
			__moduleNames.set (library, library);
			
			try {
				
				#if neko
				result = neko.Lib.loadLazy (library, method, args);
				#elseif cpp
				result = cpp.Lib.loadLazy (library, method, args);
				#end
				
			} catch (e:Dynamic) {}
			
		} else {
			
			#if (iphone || emscripten || android || static_link || tvos)
			return cpp.Lib.load (library, method, args);
			#end
			
			
			if (__moduleNames.exists (library)) {
				
				#if cpp
				return cpp.Lib.load (__moduleNames.get (library), method, args);
				#elseif neko
				return neko.Lib.load (__moduleNames.get (library), method, args);
				#elseif nodejs
				return untyped __nodeNDLLModule.load_lib (__moduleNames.get (library), method, args);
				#else
				return null;
				#end
				
			}
			
			#if waxe
			if (library == "lime") {
				
				flash.Lib.load ("waxe", "wx_boot", 1);
				
			}
			#elseif nodejs
			if (__nodeNDLLModule == null) {
				
				__nodeNDLLModule = untyped require('ndll');
				
			}
			#end
			
			__moduleNames.set (library, library);
			
			result = __tryLoad ("./" + library, library, method, args);
			
			if (result == null) {
				
				result = __tryLoad (".\\" + library, library, method, args);
				
			}
			
			if (result == null) {
				
				result = __tryLoad (library, library, method, args);
				
			}
			
			if (result == null) {
				
				var slash = (__sysName ().substr (7).toLowerCase () == "windows") ? "\\" : "/";
				var haxelib = __findHaxelib ("lime");
				
				if (haxelib != "") {
					
					result = __tryLoad (haxelib + slash + "ndll" + slash + __sysName () + slash + library, library, method, args);
					
					if (result == null) {
						
						result = __tryLoad (haxelib + slash + "ndll" + slash + __sysName() + "64" + slash + library, library, method, args);
						
					}
					
				}
				
			}
			
			__loaderTrace ("Result : " + result);
			
		}
		
		#if neko
		if (library == "lime" && method != "neko_init") {
			
			__loadNekoAPI (lazy);
			
		}
		#end
		
		#end
		#else
		
		result = function (_, _, _, _, _, _) { return { }; };
		
		#end
		
		return result;
		
	}
	
	
	public static macro function loadPrime (library:String, method:String, signature:String, lazy:Bool = false):Dynamic {
		
		#if ((haxe_ver >= 3.2) && !display)
		return cpp.Prime.load (library, method, signature, lazy);
		#else
		var args = signature.length - 1;
		
		if (args > 5) {
			
			args = -1;
			
		}
		
		return { call: CFFI.load (library, method, args, lazy) };
		#end
		
	}
	
	
	private static function __findHaxelib (library:String):String {
		
		#if (sys && !html5)
			
			try {
				
				var proc = new Process ("haxelib", [ "path", library ]);
				
				if (proc != null) {
					
					var stream = proc.stdout;
					
					try {
						
						while (true) {
							
							var s = stream.readLine ();
							
							if (s.substr (0, 1) != "-") {
								
								stream.close ();
								proc.close ();
								__loaderTrace ("Found haxelib " + s);
								return s;
								
							}
							
						}
						
					} catch(e:Dynamic) { }
					
					stream.close ();
					proc.close ();
					
				}
				
			} catch (e:Dynamic) { }
			
		#end
		
		return "";
		
	}
	
	
	private static function __loaderTrace (message:String) {
		
		#if (sys && !html5)
		#if cpp
		var get_env = cpp.Lib.load ("std", "get_env", 1);
		var debug = (get_env ("OPENFL_LOAD_DEBUG") != null);
		#else
		var debug = (Sys.getEnv ("OPENFL_LOAD_DEBUG") !=null);
		#end
		
		if (debug) {
			
			Sys.println (message);
			
		}
		#end
		
	}
	
	
	#if neko
	private static function __loadNekoAPI (lazy:Bool):Void {
		
		if (!__loadedNekoAPI) {
			
			try {
				
				var init = load ("lime", "neko_init", 5);
				
				if (init != null) {
					
					__loaderTrace ("Found nekoapi @ " + __moduleNames.get ("lime"));
					init (function(s) return new String (s), function (len:Int) { var r = []; if (len > 0) r[len - 1] = null; return r; }, null, true, false);
					
				} else if (!lazy) {
					
					throw ("Could not find NekoAPI interface.");
					
				}
				
			} catch (e:Dynamic) {
				
				if (!lazy) {
					
					throw ("Could not find NekoAPI interface.");
					
				}
				
			}
			
			__loadedNekoAPI = true;
			
		}
		
	}
	#end
	
	
	private static function __sysName ():String {
		
		#if (sys && !html5)
		#if cpp
		var sys_string = cpp.Lib.load ("std", "sys_string", 0);
		return sys_string ();
		#else
		return Sys.systemName ();
		#end
		#else
		return null;
		#end
		
	}
	
	
	private static function __tryLoad (name:String, library:String, func:String, args:Int):Dynamic {
		
		#if sys
		
		try {
			
			#if cpp
			var result = cpp.Lib.load (name, func, args);
			#elseif (neko)
			var result = neko.Lib.load (name, func, args);
			#elseif nodejs
			var result = untyped __nodeNDLLModule.load_lib (name, func, args);
			#else
			var result = null;
			#end
			
			if (result != null) {
				
				__loaderTrace ("Got result " + name);
				__moduleNames.set (library, name);
				return result;
				
			}
			
		} catch (e:Dynamic) {
			
			__loaderTrace ("Failed to load : " + name);
			
		}
		
		#end
		
		return null;
		
	}
	
	
}


#else


import haxe.macro.Context;
import haxe.macro.Expr;
import haxe.macro.Type;
import haxe.xml.Fast;
import sys.io.File;
import sys.io.FileOutput;

using haxe.macro.ComplexTypeTools;
using haxe.macro.ExprTools;
using haxe.macro.TypeTools;
using StringTools;
using Lambda;


class CFFIInterface {
	
	public var typeMaps(default, null):Map<String, Map<String, String>>;
	public var inserts(default, null):Array<String>;
	
	public function new () {
		
		typeMaps = new Map ();
		inserts = [];
		
	}
	
	public function merge (other:CFFIInterface) {
		
		for (typeMapName in other.typeMaps.keys ()) {
			
			if (!typeMaps.exists (typeMapName)) {
				
				typeMaps[typeMapName] = other.typeMaps[typeMapName];
				
			} else {
				
				var typeMap = typeMaps[typeMapName];
				var otherTypeMap = other.typeMaps[typeMapName];
				
				for (typeName in otherTypeMap.keys ()) {
					
					typeMap[typeName] = otherTypeMap[typeName];
					
				}
				
			}
			
		}
		
		for (insert in other.inserts) {
			
			inserts.push (insert);
			
		}
		
	}
	
}

enum CppArgType {
	
	InArg;
	TmpArg;
	Return;
	CFFIReturn;
	
}

class CFFI {
	
	public static var files(default, null):Array<String> = [];
	inline private static var bindingsPath:String = "../project/bindings";
	inline private static var interfacesPath:String = "../project/interfaces";
	
	public static function build (defaultLibrary:String = "lime"):Array<Field> {
		
		var cppClassName = null;
		var namespaces = null;
		var interfaceFileName = null;
		var ct = null;
		
		switch (Context.getLocalType ()) {
			
			case TInst (t, params):
				
				ct = t.get ();
				var metas = ct.meta.extract (":cffiInterface");
				if (metas.length != 0) {
					
					if (metas.length != 1) {
						
						Context.error ("A class shouldn't have more than one @:cffiInterface meta", ct.pos);
						return null;
						
					}
					
					var meta = metas[0];
					if (meta.params.length != 2) {
						
						Context.error ("@:cffiInterface exactly takes 2 param", ct.pos);
						return null;
						
					}
					
					cppClassName = meta.params[0].getValue ();
					namespaces = cppClassName.split ("::");
					interfaceFileName = meta.params[1].getValue ();
				
				}
				
			case _:
				
		}
		
		var pos = Context.currentPos ();
		var fields = Context.getBuildFields ();
		var newFields:Array<Field> = [];
		
		#if bindings
		var out = null;
		var cffiInterface = null;
		var inTypeMaps = null;
		var outTypeMaps = null;
		
		if (interfaceFileName != null) {
			
			var xmlText = File.getContent (__getInterfaceFilePath (interfaceFileName));
			var xml = Xml.parse (xmlText);
			cffiInterface = __readCFFIInterface (xml);
			
			var fileName = namespaces.join("_") + ".cpp";
			var filePath = bindingsPath + "/" + fileName;
			out = sys.io.File.write (filePath);
			files.push (fileName);
			
			for (insert in cffiInterface.inserts) {
				
				out.writeString (insert);
				
			}
			
			inTypeMaps = cffiInterface.typeMaps.get ("in");
			
			if (inTypeMaps == null) {
				
				inTypeMaps = new Map ();
				
			}
			
			outTypeMaps = cffiInterface.typeMaps.get ("out");
			
			if (outTypeMaps == null) {
				
				outTypeMaps = new Map ();
				
			}
			
		}
		#end
		
		var handleFieldName = null;
		
		for (field in fields) {
			
			switch (field) {
				
				case _ => { kind: FVar (variable), meta: meta, name: name, pos: pos } :
				case _ => { kind: FProp (get, set, t, e), meta: meta, name: name, pos: pos } :
					
					for (m in meta) {
						
						if (m.name == ":cffiHandle") {
							
							if (handleFieldName == null) {
								
								handleFieldName = name;
								
							} else {
								
								Context.error ("A class shouldn't have more than one @:cffiHandle", pos);
								return fields;
								
							}
							
						}
						
					}
					
				default:
					
			}
		}
		
		for (field in fields) {
			
			switch (field) {
				
				case _ => { kind: FFun (fun), meta: meta } :
					
					var cffiMeta = meta.find (function (v:MetadataEntry):Bool {
						
						return v.name == ":cffi";
						
					});
					
					if (cffiMeta != null) {
						
						var cffiCppTypeMeta = meta.find (function (v:MetadataEntry):Bool {
							
							return v.name == ":cffiCppType";
							
						});
						
						var funcDefLength = fun.args.length + 1;
						if (cffiCppTypeMeta != null && cffiCppTypeMeta.params.length > funcDefLength) {
							
							Context.error ("Too many number of params passed to :cffiCppType ${fun.args.length}", cffiCppTypeMeta.pos);
							return fields;
							
						}
						
						var isStatic = field.access.has(haxe.macro.Access.AStatic);
						
						if (!isStatic && handleFieldName == null) {
							
							Context.error ("Instance method is declared with @:cffi, but no field with @:cffiHandle found", ct.pos);
							return fields;
							
						}
						
						var cffiFreeAbstractMeta = meta.find (function (v:MetadataEntry):Bool {
							
							return v.name == ":cffiFreeAbstract";
							
						});
						
						if (isStatic && cffiFreeAbstractMeta != null) {
							
							Context.error ("Static method can't be declared with @:cffiFreeAbstract", cffiFreeAbstractMeta.pos);
							return fields;
							
						}
						
						var library = null;
						var method = null;
						var lazy = false;
						
						if (Reflect.hasField (cffiMeta, "params")) {
							
							if (cffiMeta.params.length > 0) library = cffiMeta.params[0].getValue ();
							if (cffiMeta.params.length > 1) method = cffiMeta.params[1].getValue ();
							if (cffiMeta.params.length > 2) lazy = cffiMeta.params[2].getValue ();
							
						}
						
						if (library == null || library == "") {
							
							library = defaultLibrary;
							
						}
						
						if (method == null || method == "") {
							
							if (namespaces == null) {
								
								method = field.name;
								
							} else {
								
								var names = namespaces.concat ([field.name]);
								method = names.join ("_");
								
							}
							
						}
						
						var typeArgs = isStatic ? [] : [ { name: '$handleFieldName', opt: false, t: ComplexTypeTools.toType (macro : Dynamic) } ];
						
						for (arg in fun.args) {
							
							typeArgs.push ( { name: arg.name, opt: false, t: arg.type.toType () } );
							
						}
						
						var type = __getFunctionType (typeArgs, fun.ret.toType ());
						
						if (!isStatic) {
							
							typeArgs.shift ();
							
						}
						
						var typeString = type.string;
						var typeSignature = type.signature;
						var expr = "";
						
						if (Context.defined ("display") || Context.defined ("disable_cffi") || Context.defined ("bindings")) {
							
							switch (type.result.toString ()) {
								
								case "Int", "Float":
									
									expr += "return 0";
								
								case "Bool":
									
									expr += "return false";
								
								default:
									
									expr += "return null";
								
							}
							
						} else {
							
							var cffiName = "cffi_" + field.name;
							var cffiExpr, cffiType;
							
							#if (haxe_ver >= 3.2)
							
							if (Context.defined ("cpp")) {
								
								cffiExpr = 'new cpp.Callable<$typeString> (cpp.Prime._loadPrime ("$library", "$method", "$typeSignature", $lazy))';
								
							} else {
								
								var args = typeSignature.length - 1;
								
								if (args > 5) {
									
									args = -1;
									
								}
								
								cffiExpr = 'new cpp.Callable<$typeString> (lime.system.CFFI.load ("$library", "$method", $args, $lazy))';
								
							}
							
							cffiType = TPath ( { pack: [ "cpp" ], name: "Callable", params: [ TPType (TFun (type.args, type.result).toComplexType ()) ] } );
							
							#else
							
							var args = typeSignature.length - 1;
							
							if (args > 5) {
								
								args = -1;
								
							}
							
							cffiExpr = 'lime.system.CFFI.load ("$library", "$method", $args, $lazy)';
							cffiType = TPath ( { pack: [ ], name: "Dynamic" } );
							
							#end
							
							newFields.push ( { name: cffiName, access: [ APrivate, AStatic ], kind: FieldType.FVar (cffiType, Context.parse (cffiExpr, field.pos)), pos: field.pos } );
							
							if (type.result.toString () != "Void" && type.result.toString () != "cpp.Void") {
								
								expr += "return ";
								
							}
							
							#if (haxe_ver >= 3.2)
							expr += '$cffiName.call (';
							#else
							expr += '$cffiName (';
							#end
							
							for (i in 0...type.args.length) {
								
								if (i > 0) expr += ", ";
								expr += type.args[i].name;
								
							}
							
							expr += ")";
							
						}
						
						//field.access.push (AInline);
						fun.expr = Context.parse (expr, field.pos);
						
						#if bindings
						if (out != null) {
							
							var params = isStatic ? [] : ["value inHandle"];
							for (i in 0 ... fun.args.length) {
								
								var arg = fun.args[i];
								var argName = renameArg (arg.name);
								params.push (__getCppType (arg.type.toType (), CppArgType.InArg) + " " + argName);
								var argTypeString = __getTypeString (cffiCppTypeMeta, i, arg.type.toType (), CppArgType.TmpArg);
								
							}
							
							var cppRetType = (cffiCppTypeMeta != null && cffiCppTypeMeta.params != null && cffiCppTypeMeta.params.length == funcDefLength) ?
								cffiCppTypeMeta.params[cffiCppTypeMeta.params.length - 1] : null;
							var cppRetTypeString = __getCppType (fun.ret.toType (), CppArgType.CFFIReturn);
							var cppTmpRetTypeString = cppRetType != null ? cppRetType.getValue () : null;
							
							if (cppTmpRetTypeString == null) {
								
								cppTmpRetTypeString = __getCppType (fun.ret.toType (), CppArgType.Return);
								
							}
							
							out.writeString (cppRetTypeString  + " " + method + "(" + params.join(", ") + ") {\n");
							
							if (!isStatic) {
								
								out.writeString ('  $cppClassName* arg1 = ($cppClassName*)NULL;\n');
								__writeTmpArgs (out, fun, 2, cffiCppTypeMeta);
								
								var classTypeMapCode = inTypeMaps.get ('$cppClassName*');
								
								if (classTypeMapCode != null) {
									
									var code = __replaceTypeMapCode (classTypeMapCode, "arg1", "inHandle");
									out.writeString (code);
									
								} else {
									
									Context.error ('in typemap for $cppClassName not found', ct.pos);
									return fields;
									
								}
								
								if (cppRetTypeString != "void") {
									
									out.writeString ("  if (arg1 == NULL) {\n");
									out.writeString ('    return ($cppRetTypeString)NULL;\n');
									out.writeString ("  }\n");
									
								} else {
									
									out.writeString ("  if (arg1 == NULL) {\n");
									out.writeString ("    return;\n");
									out.writeString ("  }\n");
									
								}
							
							} else {
								
								__writeTmpArgs (out, fun, 1, cffiCppTypeMeta);
								
							}
							
							if (cppTmpRetTypeString != "void") {
								
								out.writeString ('  $cppTmpRetTypeString result = ($cppTmpRetTypeString)NULL;\n');
								
							}
							
							var cargs = [];
							var argBase = isStatic ? 1 : 2;
							
							for (i in 0 ... fun.args.length) {
								
								var arg = fun.args[i];
								var argName = renameArg (arg.name);
								var argTypeString = __getTypeString (cffiCppTypeMeta, i, arg.type.toType (), CppArgType.TmpArg);
								
								var typeMapCode = inTypeMaps.get (argTypeString);
								var argNumber = (i + argBase);
								
								if (typeMapCode != null) {
									
									var code = __replaceTypeMapCode (typeMapCode, "arg" + (i + argBase), argName);
									out.writeString (code);
									
								} else {
									
									out.writeString ('  arg$argNumber = ${argName};\n');
									
								}
								
								cargs.push ("arg" + argNumber);
								
							}
							
							out.writeString ("  " + (cppRetTypeString != "void" ? "result = " : ""));
							out.writeString (isStatic ? '$cppClassName::${field.name}(' : 'arg1->${field.name}(');
							out.writeString (cargs.join (", ") + ");\n");
							
							if (cffiFreeAbstractMeta != null) {
								
								out.writeString ("  free_abstract (inHandle);\n");
								
							}
							
							if (cppTmpRetTypeString != "void") {
								
								var typeMapCode = outTypeMaps.get (cppTmpRetTypeString);
								
								if (typeMapCode != null) {
									
									out.writeString ("  value hxResult = (value)NULL;\n");
									var code = typeMapCode.replace ("$result", "hxResult").replace ("$input", "result");
									out.writeString (code);
									out.writeString ("  return hxResult;\n");
									
								} else {
									
									out.writeString ("  return result;\n");
									
								}
								
							}
							
							out.writeString ("}\n\n");
							out.writeString ('DEFINE_PRIME' + (fun.args.length + (isStatic ? 0 : 1)) + (cppRetTypeString == "void" ? "v" : "") + "(" + method + ");\n\n");
							
						}
						#end
						
					}
				
				default:
				
			}
			
		}
		
		#if bindings
		if (out != null) {
			
			out.close ();
			
		}
		#end
		
		fields = fields.concat (newFields);
		return fields;
		
	}
	
	
	private static function __getFunctionType (args:Array<{ name : String, opt : Bool, t : Type }>, result:Type) {
		
		#if ((haxe_ver >= 3.2) && !disable_cffi && !display)
		var useCPPTypes = Context.defined ("cpp");
		#else
		var useCPPTypes = false;
		#end
		
		var typeArgs = [];
		var typeResult = null;
		var typeSignature = "";
		
		for (arg in args) {
			
			switch (arg.t.toString ()) {
				
				case "Int", "cpp.Int16", "cpp.Int32":
					
					typeArgs.push (arg);
					typeSignature += "i";
				
				case "Bool":
					
					typeArgs.push (arg);
					typeSignature += "b";
				
				case "cpp.Float32":
					
					if (useCPPTypes) {
						
						typeArgs.push ( { name: arg.name, opt: false, t: (macro :cpp.Float32).toType () } );
						
					} else {
						
						typeArgs.push (arg);
						
					}
					
					typeSignature += "f";
				
				case "Float", "cpp.Float64":
					
					typeArgs.push (arg);
					typeSignature += "d";
				
				case "String":
					
					typeArgs.push (arg);
					typeSignature += "s";
				
				case "cpp.ConstCharStar":
					
					typeArgs.push (arg);
					typeSignature += "c";
				
				case "Void", "cpp.Void":
					
					if (useCPPTypes) {
						
						typeArgs.push ( { name: arg.name, opt: false, t: (macro :cpp.Void).toType () } );
						
					} else {
						
						typeArgs.push (arg);
						
					}
					
					typeSignature += "v";
				
				default:
					
					if (useCPPTypes) {
						
						typeArgs.push ( { name: arg.name, opt: false, t: (macro :cpp.Object).toType () } );
						
					} else {
						
						typeArgs.push ( { name: arg.name, opt: false, t: (macro :Dynamic).toType () } );
						
					}
					
					typeSignature += "o";
				
			}
			
		}
		
		switch (result.toString ()) {
			
			case "Int", "cpp.Int16", "cpp.Int32":
				
				typeResult = result;
				typeSignature += "i";
			
			case "Bool":
				
				typeResult = result;
				typeSignature += "b";
			
			case "cpp.Float32":
				
				if (useCPPTypes) {
					
					typeResult = (macro :cpp.Float32).toType ();
					
				} else {
					
					typeResult = result;
					
				}
				
				typeSignature += "f";
			
			case "Float", "cpp.Float64":
				
				typeResult = result;
				typeSignature += "d";
			
			case "String":
				
				typeResult = result;
				typeSignature += "s";
			
			case "cpp.ConstCharStar":
				
				typeResult = result;
				typeSignature += "c";
			
			case "Void", "cpp.Void":
				
				if (useCPPTypes) {
					
					typeResult = (macro :cpp.Void).toType ();
					
				} else {
					
					typeResult = result;
					
				}
				
				typeSignature += "v";
				
			default:
				
				if (useCPPTypes) {
					
					typeResult = (macro :cpp.Object).toType ();
					
				} else {
					
					typeResult = (macro :Dynamic).toType ();
					
				}
				
				typeSignature += "o";
			
		}
		
		var typeString = "";
		
		if (typeArgs.length == 0) {
			
			typeString = "Void->";
			
		} else {
			
			for (arg in typeArgs) {
				
				typeString += arg.t.toString () + "->";
				
			}
			
		}
		
		typeString += typeResult.toString ();
		
		return { args: typeArgs, result: typeResult, string: typeString, signature: typeSignature };
		
	}
	
	private static function renameArg (typeString:String) {
		
		switch (typeString) {
			
			case "value": return "_value";
			default: return typeString;
			
		}
		
	}
	
	private static function __getCppType (type:Type, argType:CppArgType):String {
		
		var typeString = type.toString ();
		switch (typeString) {
			
			case "Void": return "void";
			case "Bool": return "bool";
			case "Int": return "int";
			case "UInt": return "int32_t";
			case "Float": return "double";
			case "String":
				
				switch (argType) {
					
					case InArg: return "HxString";
					case TmpArg: return "const char*";
					default: return "value";
					
				}
			
			default:
				
				switch (argType) {
					
					case InArg, CFFIReturn:
						
						switch (typeString) {
							
							case "lime._backend.native.opengl.UniformLocation": return "int";
							default: return "value";
							
						}
						
					default:
						
						switch (typeString) {
							
							case "lime.graphics.ImageBuffer": return "lime::ImageBuffer*";
							case "lime.utils.ArrayBufferView": return "lime::ArrayBufferView*";
							case "lime._backend.native.opengl.Buffer": return "lime::GLBuffer*";
							case "lime._backend.native.opengl.Framebuffer":  return "lime::GLFramebuffer*";
							case "lime._backend.native.opengl.Program": return "lime::GLProgram*";
							case "lime._backend.native.opengl.Renderbuffer": return "lime::GLRenderbuffer*";
							case "lime._backend.native.opengl.RenderingContext": return "lime::GLRenderingContext*";
							case "lime._backend.native.opengl.Shader": return "lime::GLShader*";
							case "lime._backend.native.opengl.Texture": return "lime::GLTexture*";
							case "lime._backend.native.opengl.UniformLocation": return "int";
							default: return "value";
							
						}
						
				}
			
		}
		
	}
	
	private static function __readCFFIInterface (xml:Xml):CFFIInterface {
		
		var fast = new Fast (xml);
		var intf = new CFFIInterface ();
		
		var interfaceElement = fast.node.resolve ("interface");
		
		for (node in interfaceElement.elements) {
			
			switch (node.name) {
				
				case "typemap":
					
					var method = node.att.resolve ("method");
					var type = node.att.resolve ("type");
					
					var typeMap = intf.typeMaps.get (method);
					
					if (typeMap == null) {
						
						typeMap = new Map ();
						intf.typeMaps.set (method, typeMap);
						
					}
					
					typeMap.set (type, node.innerData);
					
				case "insert":
					
					intf.inserts.push (node.innerData);
					
				case "include":
					
					var name = node.att.resolve ("name");
					var subXmlText = File.getContent (__getInterfaceFilePath (name));
					var subXml = Xml.parse (subXmlText);
					var subIntf = __readCFFIInterface (subXml);
					
					intf.merge (subIntf);
				
			}
			
		}
		
		return intf;
		
	}
	
	private static function __getInterfaceFilePath (name:String):String {
		
		return interfacesPath + "/" + name;
		
	}
	
	private static function __writeTmpArgs (out:FileOutput, fun:haxe.macro.Function, argBase:Int, cffiCppTypeMeta:MetadataEntry):Void {
		
		for (i in 0 ... fun.args.length) {
			
			var arg = fun.args[i];
			var argNumber = (i + argBase);
			var argTypeString = __getTypeString (cffiCppTypeMeta, i, arg.type.toType (), CppArgType.TmpArg);
			
			out.writeString ('  $argTypeString arg$argNumber = ($argTypeString)NULL;\n');
			
		}
		
	}
	
	private static function __replaceTypeMapCode (typeMapCode:String, arg:String, input:String):String {
		
		return typeMapCode.replace ("$1", arg).replace ("$input", input);
		
	}
	
	private static function __getTypeString (meta:MetadataEntry, index:Int, type:haxe.macro.Type, argType:CppArgType):String {
		
		var cppType = (meta != null && meta.params != null && index < meta.params.length) ? meta.params[index] : null;
		
		if (cppType != null) {
			
			switch (cppType.expr) {
			
				case EConst (CString(s)): return s;
				default:
				
			}
		
		}
		
		return __getCppType (type, argType);
		
	}
	
}


#end